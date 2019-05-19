#include "sys.h"
#include "usart.h"	
//#include "exti.h"

/**
 *���ƣ�USART_Config
 *������void
 *����ֵ��void
 *���ܣ�USART��ʼ������
 */

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitSturcture;
	USART_InitTypeDef USART_InitStructure;
	
	/* �򿪴���GPIO��ʱ�� */
	DEBUG_USART_GPIO_APBxCLKCmd(DEBUG_USART_GPIO_CLK,ENABLE);
	/* �򿪴��������ʱ�� */
	DEBUG_USART_APBxCLKCmd(DEBUG_USART_CLK,ENABLE);
	
	/* ��USART Tx��GPIO����Ϊ���츴��ģʽ */
	GPIO_InitSturcture.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT,&GPIO_InitSturcture);
	
	/* ��USART Rx��GPIO����Ϊ��������ģʽ */
	GPIO_InitSturcture.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT,&GPIO_InitSturcture);
	
	/* ���ô��ڵĹ������� */
	/* ������ */
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	/* ֡�����ֳ� */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ֹͣλ */
	USART_InitStructure.USART_StopBits = USART_Parity_No;
	/* У��λ */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* Ӳ�������� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* �շ�ģʽ */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ��ɴ��ڳ�ʼ������ */
	USART_Init(DEBUG_USARTx,&USART_InitStructure);
	
	/* �����ж����ȼ����� */
//	NVIC_Configuration();
	/* ʹ�ܴ��ڽ����ж� */	
//	USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);
	/* ʹ�ܴ��� */
	USART_Cmd(DEBUG_USARTx,ENABLE);
}

/**
 *���ƣ�Usart_SendByte
 *������* pUSARTx, ch
 *����ֵ��void
 *���ܣ�����һ���ַ�
 */
void Usart_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
	/* �ȴ��������ݼĴ���Ϊ�� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE) == RESET);
}

/**
 *���ƣ�Usart_SendString
 *������* pUSARTx, str
 *����ֵ��void
 *���ܣ������ַ���
 */
void Usart_SendString(USART_TypeDef * pUSARTx, char * str)
{
	unsigned int k = 0;
	do{
		Usart_SendByte(pUSARTx,*(str + k));
		k++;
	}while(*(str + k)!='\0');
	
	/*�ȴ��������*/
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC) == RESET){
	}
}

/**
 *���ƣ�fputc
 *������ch, *f
 *����ֵ��ch
 *���ܣ��ض���C�⺯��printf�����ڣ��Ա�ʹ��printf
 */
int fputc(int ch, FILE *f)
{
	USART_SendData(DEBUG_USARTx,(uint8_t)ch);
	while (USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TXE) == RESET);
	return ch;
}

/**
 *���ƣ�fgetc
 *������*f
 *����ֵ��(int)USART_ReceiveData(DEBUG_USARTx)
 *���ܣ��ض���C�⺯��scanf�����ڣ��Ա�ʹ��scanf,getchar
 */
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(DEBUG_USARTx);
}


