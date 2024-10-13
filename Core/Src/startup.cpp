//
// Created by Sunny on 24-10-12.
//

#include "startup.h"
#include "RC.h"
#include "usart.h"

extern uint8_t rx_buf_[];

void startup()
{
	RC_init();
	while(1)
	{

	}
}
