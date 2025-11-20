#include <stdio.h>
#include <string.h>
#include <math.h>


#include "ls1b.h"
#include "mips.h"
#include "bsp.h"
#include "ns16550.h"
#include "libc/lwmem.h"
#include "ls1x_fb.h"
#include "ls1b_gpio.h"


char LCD_display_mode[] = LCD_480x800;

//错误处理常量定义
#define ERROR_NONE       0      //无错误
#define ERROR_FORMAT     1      //格式错误
#define ERROR_DIV_ZERO   2      //除数不能为零
#define ERROR_INVALID_OP 3      //无效运算符


int main(void)
{
    printk("\r\n串口计算器 + LCD显示 程序启动！\r\n");

   
    lwmem_initialize(0);  
    gpio_enable(2, DIR_OUT);
    gpio_write(2, 1);
    gpio_enable(54, DIR_OUT);
    gpio_write(54, 1);
    gpio_enable(3, DIR_OUT);
    gpio_write(3, 1);

    fb_open();  
    int xres = fb_get_pixelsx();  
    int yres = fb_get_pixelsy();  
    printk("LCD分辨率：%d x %d\n", xres, yres);
    
    //清屏
    fb_cons_clear();  


   
    unsigned int baud = 115200;
    ls1x_uart_init(devUART5, (void *)baud);  
    ls1x_uart_open(devUART5, NULL);         


    
    char rdbuf[256] = {0}, wrbuf[256] = {0};  
    int len, result, error;
    char op;  

    while(1)
    {
        
        len = ls1x_uart_read(devUART5, rdbuf, 256, NULL);
        if(len > 0)
        {
            
            printk("\n收到上位机数据: %s\n", rdbuf);

            error = cal_data(rdbuf, len, &result, &op);

            
            if(error == ERROR_NONE)
            {
                sprintf(wrbuf, "上位机结果: %s=%d\n", rdbuf, result);
            }
            else if(error == ERROR_FORMAT)
            {
                sprintf(wrbuf, "错误：格式不正确！请用 xx+xx 格式（支持+、-、*、/）\n");
            }
            else if(error == ERROR_DIV_ZERO)
            {
                sprintf(wrbuf, "错误：除法时除数不能为0！\n");
            }
            else if(error == ERROR_INVALID_OP)
            {
                sprintf(wrbuf, "错误：无效运算符！只支持 +、-、*、/\n");
            }
            ls1x_uart_write(devUART5, wrbuf, strlen(wrbuf), NULL);  


           
            fb_cons_clear();  
            
            fb_textout(100, 100, "收到运算指令：");
            fb_textout(100, 130, rdbuf);              

           
            if(error == ERROR_NONE)
            {
                char lcd_result[256];
                sprintf(lcd_result, "计算结果：%s=%d", rdbuf, result);
                fb_textout(100, 160, lcd_result);  
            }
            else
            {
                fb_textout(100, 160, wrbuf);  
            }


            
            memset(rdbuf, 0, 256);
            memset(wrbuf, 0, 256);
        }
        delay_ms(100);  
    }

    return 0;
}



int cal_data(char *rdbuf, int len, int *result, char *op)
{
    int i, op_pos = -1;  
    int num1 = 0, num2 = 0;  

     // 步骤1：过滤首尾的换行符、回车符、空格
    int start = 0, end = len - 1;
    while(start <= end && (rdbuf[start] == '\r' || rdbuf[start] == '\n' || rdbuf[start] == ' '))
        start++;
    while(end >= start && (rdbuf[end] == '\r' || rdbuf[end] == '\n' || rdbuf[end] == ' '))
        end--;
    len = end - start + 1; // 有效数据长度
    if(len <= 2) return ERROR_FORMAT; // 至少需要"x+y"格式（长度3）
    
    // 步骤2：查找运算符（仅保留有效数据段）
    //  12  +   23
    for(i = start; i <= end; i++)
    {
        if(rdbuf[i] == '+' || rdbuf[i] == '-' || rdbuf[i] == '*' || rdbuf[i] == '/')
        {
            if(op_pos != -1)  
                return ERROR_FORMAT;
            op_pos = i;
            *op = rdbuf[i];
        }
    }

    // 步骤3：校验运算符位置（有效数据段内）
    if(op_pos == -1 || op_pos == 0 || op_pos == len-1)
        return ERROR_FORMAT;

    // 步骤4：解析第一个数字（有效数据段内）
    for(i = 0; i < op_pos; i++)
    {
        char c = rdbuf[start + i];
        if(c < '0' || c > '9')
            return ERROR_FORMAT;
        num1 = num1 * 10 + (c - '0');
    }

    // 步骤5：解析第二个数字（有效数据段内）
    for(i = op_pos + 1; i < len; i++)
    {
        char c = rdbuf[start + i];
        if(c < '0' || c > '9')
            return ERROR_FORMAT;
        num2 = num2 * 10 + (c - '0');
    }

   // 步骤6：计算结果
    switch(*op)
    {
        case '+': *result = num1 + num2; break;
        case '-': *result = num1 - num2; break;
        case '*': *result = num1 * num2; break;
        case '/':
            if(num2 == 0) return ERROR_DIV_ZERO;
            *result = num1 / num2;  
            break;
        default: return ERROR_INVALID_OP;
    }

    return ERROR_NONE;
}
