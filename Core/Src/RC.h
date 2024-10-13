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

typedef enum{UP_POS, DOWN_POS, MID_POS}  RCSwitchState_e;
const RCSwitchState_e RCSwitchStates[] = {UP_POS, DOWN_POS, MID_POS};

typedef enum{MOUSE_UP, MOUSE_DOWN}  RCMouseClickState_e;
const RCMouseClickState_e RCMouseClickStates[] = {MOUSE_UP, MOUSE_DOWN};

struct RCChannel{
	float r_row;
	float r_col;
	float l_row;
	float l_col;
};

struct RCSwitch {
	RCSwitchState_e l;
	RCSwitchState_e r;
};

struct RCMouse {
	float x;
	float y;
	float z;

	RCMouseClickState_e l;
	RCMouseClickState_e r;
};

class RC{
private:

public:

	static RCChannel  channel_;
	static RCSwitch switch_;
	static RCMouse mouse_;
	static uint8_t keys_;

	static void init();
	static void frameHandle();
};

enum {RC_KEY_W, RC_KEY_S, RC_KEY_A, RC_KEY_D, RC_KEY_Q, RC_KEY_E, RC_KEY_SHIFT, RC_KEY_CTRL};

void RC_init();

#endif
