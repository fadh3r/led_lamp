#include "stm32l1xx.h"
#define BLUE_LED_ON GPIOB->ODR |= GPIO_ODR_ODR_6
#define BLUE_LED_OFF GPIOB->ODR &= ~GPIO_ODR_ODR_6
#define GREEN_LED_ON GPIOB->ODR |= GPIO_ODR_ODR_7
#define GREEN_LED_OFF GPIOB->ODR &= ~GPIO_ODR_ODR_7
#define BUTTON_ON (GPIOA->IDR & GPIO_IDR_IDR_0)
#define BUTTON_OFF (!(GPIOA->IDR & GPIO_IDR_IDR_0))


void USART_Init(){
	RCC->CR |= RCC_CR_HSION; //Включаем тактовый генератор HSI
	while(!(RCC->CR & RCC_CR_HSIRDY)); //Ждем его стабилизации
	RCC->CFGR |= RCC_CFGR_SW_HSI; //Выбираем источником тактовой частоты SYSCLK генератор HSI
	RCC->CR &= ~RCC_CR_MSION; //Отключаем генератор MSI.
	//GPIOA CONFIGURATION
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;	
	GPIOA -> MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);//AF for PA9 and PA10
	GPIOA -> OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR9_1 | GPIO_OSPEEDER_OSPEEDR10_1);
	GPIOA -> OTYPER &= ~(GPIO_OTYPER_OT_9);//push-pull for output
 	GPIOA -> PUPDR &= ~(GPIO_PUPDR_PUPDR10);//no pull-up, pull-down for input
 	GPIOA -> AFR[1] |= (0x770);//afio7 for pa9 - USART1_TX and pa10 - USART1_RX
 	//USART CONFIGURATION
 	NVIC_EnableIRQ (USART1_IRQn);
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;//USART CLOCK ENABLE
	USART1 -> BRR = 0x683; //9600 baud rate 0x683
	USART1 -> CR1  |= USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE | USART_CR1_UE | USART_CR1_TXEIE;//enable: recive, transimt, USART, Interrupt Read Data not empty


void Usart_Init(void);
void Usart_Write(char);
void Usart_Read(char);



Usart_Init();

while(1){
if BUTTON_ON{
Usart_Write('H');
Usart_Write('e');
Usart_Write('l');
Usart_Write('l');
Usart_Write('o');
Usart_Write(' ');

}


}
}

	







	
void Usart_Write(char data)
{
  while(!(USART1->SR & USART_SR_TC)); //Проверка завершения передачи предыдущих данных
  USART1->DR = data; //Передача данных
}

void Usart_Read(char data)
{
  while(!(USART1->SR & USART_SR_RXNE)); //Проверка завершения приёма предыдущих данных
  data = USART1->DR; //Передача данных

}


void USART1_IRQHandler(void){
	char data;
	if(USART1->SR & USART_SR_RXNE){//Read data register not empty
		Usart_Read(data = USART1->DR);     
	}


		if(USART1->SR & USART_SR_TC){
		}
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
