#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
 static void Show_Message(void);
 int main(void)
 {	
	 char ch;
	 LED_Init();
	 USART_Config();
	 Show_Message();
	 while(1)
	{
		ch = getchar();
		printf("收到 %c\n",ch);
		switch(ch)
		{
			case '1':
				GPIO_ResetBits(GPIOA,GPIO_Pin_8); 
				GPIO_SetBits(GPIOD,GPIO_Pin_2);
				break;
			case '2':
				GPIO_SetBits(GPIOA,GPIO_Pin_8);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2);
				break;
			case '3':
				GPIO_SetBits(GPIOA,GPIO_Pin_8);
				GPIO_SetBits(GPIOD,GPIO_Pin_2);
				break;
			default:
        /* 如果不是指定指令字符，打印提示信息 */
        Show_Message();
        break;  
		}
	 }
}


/**
 *名称：Show_Message
 *参数：void
 *返回值：void
 *功能：显示提示信息
 */
 static void Show_Message(void)
{
  printf("\r\n   这是一个通过串口指令控制LED灯实验 \n");
  printf("开发板接到指令后控制LED灯颜色，指令对应如下：\n");
  printf("指令   ------ LED灯号 \n");
  printf("1    ------    LED1 \n");
  printf("2    ------    LED2 \n");
  printf("3    ------    灭 \n");  
}


