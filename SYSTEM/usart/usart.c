#include "sys.h"
#include "usart.h"	
//#include "exti.h"

/**
 *名称：USART_Config
 *参数：void
 *返回值：void
 *功能：USART初始化配置
 */

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitSturcture;
	USART_InitTypeDef USART_InitStructure;
	
	/* 打开串口GPIO的时钟 */
	DEBUG_USART_GPIO_APBxCLKCmd(DEBUG_USART_GPIO_CLK,ENABLE);
	/* 打开串口外设的时钟 */
	DEBUG_USART_APBxCLKCmd(DEBUG_USART_CLK,ENABLE);
	
	/* 将USART Tx的GPIO配置为推挽复用模式 */
	GPIO_InitSturcture.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT,&GPIO_InitSturcture);
	
	/* 将USART Rx的GPIO配置为浮空输入模式 */
	GPIO_InitSturcture.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT,&GPIO_InitSturcture);
	
	/* 配置串口的工作参数 */
	/* 波特率 */
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	/* 帧数据字长 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位 */
	USART_InitStructure.USART_StopBits = USART_Parity_No;
	/* 校验位 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* 收发模式 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成串口初始化配置 */
	USART_Init(DEBUG_USARTx,&USART_InitStructure);
	
	/* 串口中断优先级配置 */
//	NVIC_Configuration();
	/* 使能串口接收中断 */	
//	USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);
	/* 使能串口 */
	USART_Cmd(DEBUG_USARTx,ENABLE);
}

/**
 *名称：Usart_SendByte
 *参数：* pUSARTx, ch
 *返回值：void
 *功能：发送一个字符
 */
void Usart_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
	/* 等待发送数据寄存器为空 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE) == RESET);
}

/**
 *名称：Usart_SendString
 *参数：* pUSARTx, str
 *返回值：void
 *功能：发送字符串
 */
void Usart_SendString(USART_TypeDef * pUSARTx, char * str)
{
	unsigned int k = 0;
	do{
		Usart_SendByte(pUSARTx,*(str + k));
		k++;
	}while(*(str + k)!='\0');
	
	/*等待发送完成*/
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC) == RESET){
	}
}

/**
 *名称：fputc
 *参数：ch, *f
 *返回值：ch
 *功能：重定向C库函数printf到串口，以便使用printf
 */
int fputc(int ch, FILE *f)
{
	USART_SendData(DEBUG_USARTx,(uint8_t)ch);
	while (USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TXE) == RESET);
	return ch;
}

/**
 *名称：fgetc
 *参数：*f
 *返回值：(int)USART_ReceiveData(DEBUG_USARTx)
 *功能：重定向C库函数scanf到串口，以便使用scanf,getchar
 */
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(DEBUG_USARTx);
}


