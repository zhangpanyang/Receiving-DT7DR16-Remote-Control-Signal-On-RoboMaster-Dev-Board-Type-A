//
// Created by Sunny on 24-10-12.
//

#include "startup.h"
#include "RC.h"
#include "usart.h"

extern uint8_t rx_buf_[];

void startup()
{
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buf_, RC_RX_BUF_SIZE);
	RC_init();
	while(1)
	{

	}
}
