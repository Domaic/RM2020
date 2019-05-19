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
		printf("�յ� %c\n",ch);
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
        /* �������ָ��ָ���ַ�����ӡ��ʾ��Ϣ */
        Show_Message();
        break;  
		}
	 }
}


/**
 *���ƣ�Show_Message
 *������void
 *����ֵ��void
 *���ܣ���ʾ��ʾ��Ϣ
 */
 static void Show_Message(void)
{
  printf("\r\n   ����һ��ͨ������ָ�����LED��ʵ�� \n");
  printf("������ӵ�ָ������LED����ɫ��ָ���Ӧ���£�\n");
  printf("ָ��   ------ LED�ƺ� \n");
  printf("1    ------    LED1 \n");
  printf("2    ------    LED2 \n");
  printf("3    ------    �� \n");  
}


