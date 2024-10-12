//
// Created by Sunny on 24-10-12.
//

#ifndef RC_H
#define RC_H

#include "main.h"

const int RC_RX_BUF_SIZE = 18;
const int RC_RX_DATA_SIZE = 18;

enum RCSwitchState_e {UP_POS, MID_POS, DOWN_POS};

class RC{
private:
	uint8_t rx_buf_[RC_RX_BUF_SIZE] = {};
	uint8_t rx_data_[RC_RX_DATA_SIZE] = {};

public:
	struct RCChannel{
		float r_row;
		float r_col;
		float l_row;
		float l_col;
	} channel_;
	struct RCSwitch {
		RCSwitchState_e l;
		RCSwitchState_e r;
	} switch_;

	void init();

};



#endif //RC_H
