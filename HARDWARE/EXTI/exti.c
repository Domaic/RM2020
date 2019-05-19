#include "sys.h"
#include "exti.h"	
#include "usart.h"
/**
 *名称：NVIC_Configuration
 *参数：void
 *返回值：void
 *功能：配置中断控制器
 */
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

	/* 嵌套向量中断控制器组选择 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* 配置USART为中断源 */
    NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
	/* 抢占优先级为1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 子优先级为1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* 初始化配置NVIC */
	NVIC_Init(&NVIC_InitStructure);
}

/**
 *名称：DEBUG_USART_IRQHandler
 *参数：void
 *返回值：void
 *功能：读取数据并发送给源设备
 */

void DEBUG_USART_IRQHandler(void)
{
	uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET){
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
		USART_SendData(DEBUG_USARTx,ucTemp);
	}
}
