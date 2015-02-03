#include <string.h>
#include <stdint.h>
#include <cstdlib>
#include "parsing.h"
#include "cmdstructure.h"
#include "color_control.h"
#include "esp_init.h"
char CmdDataArray[10];
uint8_t ArrI=0;

	
void ExecuteCommand()
	{
		Color_SetR(*RED);
		Color_SetG(*GREEN);
		Color_SetB(*BLUE);
	}
void Usart_Parsing()
	{	
		if(strncmp(CmdDataArray, "OK",2)==0)
			{
				ESP_Init(CmdDataArray);
			}
		char *p=strtok(CmdDataArray, ",");
		LampCmdStructure.CmdStructArr[0]=atoi(p);//array to structure cycle
		uint8_t i=0;
		while(p)
			{	
				p=strtok(NULL, ",");
				LampCmdStructure.CmdStructArr[++i]=atoi(p);				
			}
		ExecuteCommand();			
	}

void Data_Received(char data)
	{
		if(data==0x0D)
			{
			CmdDataArray[ArrI]=0;
			ArrI=0;
			Usart_Parsing();
			}
		else
			{
			CmdDataArray[ArrI]=data;
			ArrI++;
			}
	}