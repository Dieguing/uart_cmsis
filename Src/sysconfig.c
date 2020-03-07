#include "sysconfig.h"
#include "stm32l0xx.h"    

void SystemConfig(){
	/* Enable GPIOA clock */
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	/* Configure GPIOA pin 5 as output */
	GPIOA->MODER = 0xEBFFF7FF;
	/* Configure GPIOA pin 5 in max speed */
	GPIOA->OSPEEDR |= (3 << (LED_PIN * 2));
}

void _delay(){
	for (uint32_t i = 0; i < 100000 ; i++);
}
