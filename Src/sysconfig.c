#include "sysconfig.h"
#include "stm32l0xx.h"    

void SystemConfig(){
	
	//============ PA5 LED configuration =======================
	/* Enable GPIOA clock */
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	/* Configure GPIOA pin 5 as output */
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE5_1));
	/* Configure GPIOA pin 5 in max speed */
	GPIOA->OSPEEDR |= (3 << (LED_PIN * 2));
	
	//============ PC13 Button configuration =======================
	/* Enable the peripheral clock of GPIOC */
  RCC->IOPENR |= RCC_IOPENR_IOPCEN;
		/* Select input mode (00) on PC13 */
  GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODE13));
	
	/* Configure Syscfg, exti and nvic for pushbutton PC13 */
	/* Enable the clock of System Configurator Controller */
	/*This setting is very important for correct working of EXTI*/
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  /* (1) PC13 as source input on register EXTICR4*/
  /* (2) Unmask port 13 */
  /* (3) Falling edge */
  /* (4) Set priority */
  /* (5) Enable EXTI4_15_IRQn */
  SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~SYSCFG_EXTICR4_EXTI13) | SYSCFG_EXTICR4_EXTI13_PC; /* (1) */ 
  EXTI->IMR |= EXTI_IMR_IM13; /* (2) */ 
  EXTI->FTSR |= EXTI_FTSR_FT13; /* (3) */ 
  NVIC_SetPriority(EXTI4_15_IRQn, 0); /* (4) */ 
  NVIC_EnableIRQ(EXTI4_15_IRQn); /* (5) */ 
		
	//========== UART configuration ================================
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
	
	while((USART2->ISR & USART_ISR_TC) != USART_ISR_TC){};
  USART2->ICR = USART_ICR_TCCF;/* clear TC flag */
	
	/* Enable Transmission Complete Interrupt */
	USART2->CR1 |= USART_CR1_TCIE;
	
	/* Configure IT */
  /*Set priority for USART2_IRQn */
  NVIC_SetPriority(USART2_IRQn, 0);
	/* Enable USART2_IRQn */
  NVIC_EnableIRQ(USART2_IRQn);

	
}

void _delay(){
	for (uint32_t i = 0; i < 100000 ; i++);
}
