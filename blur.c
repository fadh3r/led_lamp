#include <stm32l1xx.h>
#include <stdint.h>
#include "color_control.h"
#include "timers.h"
extern unsigned char *CmdByte;
extern uint8_t *R_current, *R_received, *G_current, *G_received, *B_current, *B_received;


void Blur()
{
	uint8_t time=1;
	//if(*CmdByte=='s')
if(*R_current<*R_received)
	while(*R_current<*R_received)
	{
		*R_current=*R_current+time;
		Color_SetR(*R_current);
		Delay_msec(1);
	}
	
if(*R_current>*R_received)
	while(*R_current>*R_received)
	{
		*R_current=*R_current-time;
		Color_SetR(*R_current);
		Delay_msec(1);
	}
}

