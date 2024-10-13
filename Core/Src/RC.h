//
// Created by Sunny on 24-10-12.
//

#ifndef RC_H
#define RC_H

#include "main.h"

float linearMappingInt2Float(int in,int in_min,int in_max,float out_min,float out_max);
int linearMappingFloat2Int(float in,float in_min,float in_max,int out_min,int out_max);

const int RC_RX_BUF_SIZE = 18;
const int RC_RX_DATA_SIZE = 18;

typedef enum{UP_POS, MID_POS, DOWN_POS}  RCSwitchState_e;

class RC{
private:
	static uint8_t rx_buf_[RC_RX_BUF_SIZE];
	static uint8_t rx_data_[RC_RX_DATA_SIZE];

public:
	static struct RCChannel{
		float r_row;
		float r_col;
		float l_row;
		float l_col;
	} channel_;
	static struct RCSwitch {
		RCSwitchState_e l;
		RCSwitchState_e r;
	} switch_;

	static void init();
	static void frameHandle();
};
uint8_t RC::rx_buf_[RC_RX_BUF_SIZE];
uint8_t RC::rx_data_[RC_RX_DATA_SIZE];
// struct RC::RCChannel;
// struct RC::RCSwitch;



#endif //RC_H
