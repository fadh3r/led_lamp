#include <string.h>
#include <stdint.h>
#include "usart.h"
#include "parsing.h"
uint8_t N=0;

void ESP_Init(char *CmdDataArrayPtr)
	{
		char *initstring1="AT+CWMODE=1//station mode\n\r\0";
		char *initstring2="AT+CIPMODE=0//full duplex transmisson mode\n\r\0";
		char *initstring3="AT+CIPMUX=0//single connection mode\n\r\0";
		char *ESP_Init_Array[]={initstring1, initstring2, initstring3};

		if(strcmp(CmdDataArrayPtr, "start")==0)
			Usart_SendString("Starting ESP8266 initialization...\n\r\0");
		if(strcmp(CmdDataArrayPtr, "OK\0")==0)
			{
				Usart_SendString(ESP_Init_Array[N]);
				N++;
			}
		if(N==4)
			Usart_SendString("ESP8266 online...");
	}













/*AT Command ends with “\r\n”
AT
	:OK

AT+CWMODE=1//station mode
	:OK

AT+CWJAP="kaa","19562876"
	:OK

AT+CIFSR//IP
	:+CIFSR:STAIP,"192.168.0.5"
	:+CIFSR:STAMAC,"18:fe:34:9d:f9:1c"

AT+CIPMODE=0//full duplex transmisson mode
	:OK

AT+CIPMUX=0//single connection mode
	:OK

AT+CIPSERVER=1,8888//start server on 8888 port
	:OK
	
AT+CIPSTATUS
	:STATUS:4//diconected
	:OK
	or
	:STATUS:3//conected
	:+CIPSTATUS:0,"TCP","192.168.0.2",51738,1//0- id, type, ip, port, server(1) or client(0)
	:OK

sending from PC:
after connect: CONNECT
		:+IPD,4:test	//+IPD,<length>:<data>
		:OK
		:+IPD,0,2:
		:OK

sending from ESP:
AT+CIPSEND=4		//char number
> test					//without enter
	:SEND OK

*/