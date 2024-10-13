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

uint8_t rx_buf_[RC_RX_BUF_SIZE];
uint8_t rx_data_[RC_RX_DATA_SIZE];
RCChannel RC::channel_;
RCSwitch RC::switch_;
RCMouse RC::mouse_;
uint8_t RC::keys_;

void RC::init()
{
	channel_.l_col = 0;
	channel_.l_row = 0;
	channel_.r_col = 0;
	channel_.r_row = 0;
	switch_.l = MID_POS;
	switch_.r = MID_POS;
}

void RC_init()
{
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buf_, RC_RX_BUF_SIZE);
	RC::init();
	memset(rx_buf_, 0, sizeof(rx_buf_));
	memset(rx_data_, 0, sizeof(rx_data_));
}


int cnt = 0;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	cnt ++;
	if (huart == &huart1)
	{
		std::memcpy(rx_buf_, rx_data_, sizeof(rx_buf_));
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buf_, RC_RX_BUF_SIZE);
		if (Size == RC_RX_BUF_SIZE)
		{
			RC::frameHandle();
		}
	}
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
	channel_.r_row = linearMappingInt2Float((uint16_t)rx_data_[0]<<3 | rx_data_[1]>>5,										364, 1684, -1.0, 1.0);
	channel_.l_col = linearMappingInt2Float((uint16_t)(rx_data_[1]&0x1f)<<6 | rx_data_[2]>>2,								364, 1684, -1.0, 1.0);
	channel_.r_col = linearMappingInt2Float((uint16_t)(rx_data_[2]&0x03)<<9 | (uint16_t)rx_data_[3]<<1 | rx_data_[4]>>7,	364, 1684, -1.0, 1.0);
	channel_.l_row = linearMappingInt2Float((uint16_t)(rx_data_[4]&0x7f)<<4 | rx_data_[5]>>4,								364, 1684, -1.0, 1.0);

	switch_.r = RCSwitchStates[ (rx_data_[5]>>2 & 0x03) - 1 ];
	switch_.l = RCSwitchStates[ (rx_data_[5] & 0x03) - 1 ];

	mouse_.x = linearMappingInt2Float( (uint16_t)((uint16_t)rx_data_[6]<<8 | rx_data_[7]), -32768, 32767, -1.0, 1.0);
	mouse_.y = linearMappingInt2Float( (uint16_t)((uint16_t)rx_data_[8]<<8 | rx_data_[9]), -32768, 32767, -1.0, 1.0);
	mouse_.z = linearMappingInt2Float( (uint16_t)((uint16_t)rx_data_[10]<<8 | rx_data_[11]), -32768, 32767, -1.0, 1.0);

	mouse_.l = RCMouseClickStates[ rx_data_[12] ];
	mouse_.l = RCMouseClickStates[ rx_data_[13] ];

	keys_ = rx_data_[14];
}
