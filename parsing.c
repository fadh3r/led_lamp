#include <string.h>
#include <stdint.h>
#include <cstdlib>
#include "parsing.h"
#include "cmdstructure.h"
#include "color_control.h"
#include "esp_init.h"
char CmdDataArray[100];
uint8_t ArrI=0;

	
void ExecuteCommand()
	{
		Color_SetR(*RED);
		Color_SetG(*GREEN);
		Color_SetB(*BLUE);
	}
void Usart_Parsing()
	{
		uint8_t i=0;
		while(i<ArrI)
			{
				if(CmdDataArray[i]=='O'&&CmdDataArray[i+1]=='K')
						ESP_Init(CmdDataArray);
				i++;
			}
		i=0;
		ArrI=0;
		char *p=strtok(CmdDataArray, ",");
		LampCmdStructure.CmdStructArr[0]=atoi(p);//array to structure cycle
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
			Usart_Parsing();
			ArrI=0;
			}
		else
			{
			CmdDataArray[ArrI]=data;
			ArrI++;
			}
	}
