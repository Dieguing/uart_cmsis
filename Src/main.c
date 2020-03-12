#include "sysconfig.h"
#include "stm32l0xx.h"

int main() {
	/*	At this stage the microcontroller clock setting is already configured, 
      this is done through SystemInit() function which is called from startup
      file (startup_stm32l0xx.s) before to branch to application main.
      To reconfigure the default setting of SystemInit() function, refer to
      system_stm32l0xx.c file */

	SystemConfig();

	while(1){
		/* Turn on the LED */
		LED_ON();
		USART2->TDR = 'O';
		while((USART2->ISR & USART_ISR_TC) != USART_ISR_TC);
		USART2->ICR = USART_ICR_TCCF;
		USART2->TDR = 'K';
		while((USART2->ISR & USART_ISR_TC) != USART_ISR_TC);
		USART2->ICR = USART_ICR_TCCF;
		USART2->TDR = 10;
		while((USART2->ISR & USART_ISR_TC) != USART_ISR_TC);
		USART2->ICR = USART_ICR_TCCF;
		_delay();
		LED_OFF();
		_delay();
	}
}
