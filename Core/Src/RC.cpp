//
// Created by Sunny on 24-10-12.
//

#include "RC.h"
#include "usart.h"
#include <cstring>

float linearMappingInt2Float(int in,int in_min,int in_max,float out_min,float out_max) {
	return (out_max-out_min)*(float)(in-in_min)/(float)(in_max-in_min)+out_min;
}
int linearMappingFloat2Int(float in,float in_min,float in_max,int out_min,int out_max) {
	return (out_max-out_min)*(in-in_min)/(in_max-in_min)+out_min;
}

void RC::init()
{
	memset(rx_buf_, 0, sizeof(rx_buf_));
	memset(rx_data_, 0, sizeof(rx_data_));
	channel_.l_col = 0;
	channel_.l_row = 0;
	channel_.r_col = 0;
	channel_.r_row = 0;
	switch_.l = MID_POS;
	switch_.r = MID_POS;

	HAL_UART_Receive_DMA(&huart1, rx_buf_, RC_RX_BUF_SIZE);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
	{
		RC::frameHandle();
	}
}

void RC::frameHandle()
{
	std::memcpy(rx_buf_, rx_data_, sizeof(rx_buf_));
	std::memset(rx_buf_, 0, sizeof(rx_buf_));
}
