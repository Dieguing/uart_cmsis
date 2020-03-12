#include "sysconfig.h"
#include "stm32l0xx.h"    

void SystemConfig(){
	/* Enable GPIOA clock */
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	/* Configure GPIOA pin 5 as output */
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE5_1));
	/* Configure GPIOA pin 5 in max speed */
	GPIOA->OSPEEDR |= (3 << (LED_PIN * 2));
	//PA2 Tx and PA3 Rx as Alternate Function	
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE2|GPIO_MODER_MODE3)) | (GPIO_MODER_MODE2_1|GPIO_MODER_MODE3_1);
	//Configuration of Alternate Function register
  GPIOA->AFR[0] = (GPIOA->AFR[0] & ~(GPIO_AFRL_AFSEL2|GPIO_AFRL_AFSEL3)) | ((4<<GPIO_AFRL_AFSEL2_Pos) | (4<<GPIO_AFRL_AFSEL3_Pos));
	
	/* Enable the peripheral clock USART2 */
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	/* Oversampling by 16, 9600 baud */
	USART2->BRR = SystemCoreClock / 9600;
	/* USART enable and Tx enable*/
  USART2->CR1 = USART_CR1_TE|USART_CR1_UE;
	
	//while((USART2->ISR & USART_ISR_TC) != USART_ISR_TC);
  //USART2->ICR = USART_ICR_TCCF; // clear TC flag transmission complete

	
}

void _delay(){
	for (uint32_t i = 0; i < 100000 ; i++);
}
