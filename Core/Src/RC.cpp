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

	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buf_, RC_RX_BUF_SIZE);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == &huart1)
	{
		if (Size == RC_RX_BUF_SIZE)
		{
			RC::frameHandle();
		}
	}
}

void RC::frameHandle()
{
	std::memcpy(rx_buf_, rx_data_, sizeof(rx_buf_));
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buf_, RC_RX_BUF_SIZE);

	channel_.r_row = linearMappingInt2Float((uint16_t)rx_data_[0]<<3 | rx_data_[1]>>5,										364, 1684, -1.0, 1.0);
	channel_.l_col = linearMappingInt2Float((uint16_t)(rx_data_[1]&0x1f)<<6 | rx_data_[2]>>2,								364, 1684, -1.0, 1.0);
	channel_.r_col = linearMappingInt2Float((uint16_t)(rx_data_[2]&0x03)<<9 | (uint16_t)rx_data_[3]<<1 | rx_data_[4]>>7,	364, 1684, -1.0, 1.0);
	channel_.l_row = linearMappingInt2Float((uint16_t)(rx_data_[4]&0x7f)<<4 | rx_data_[5]>>4,								364, 1684, -1.0, 1.0);

	switch_.r = RCSwitchStates[ (rx_data_[5]>>2 & 0x03) - 1 ];
	switch_.l = RCSwitchStates[ (rx_data_[5] & 0x03) - 1 ];

}
