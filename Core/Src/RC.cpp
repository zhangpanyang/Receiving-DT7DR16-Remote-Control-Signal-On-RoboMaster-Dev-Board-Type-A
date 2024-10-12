//
// Created by Sunny on 24-10-12.
//

#include "RC.h"

#include <string.h>

float linearMap(int oriMin, int oriMax, float tarMin, float tarMax, int x)
{
	return (x - oriMin) * (tarMax - tarMin) / (float)(oriMax - oriMin) + tarMin;
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
}
