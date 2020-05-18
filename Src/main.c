#include "sysconfig.h"
#include "stm32l0xx.h"

uint8_t send = 0;
uint8_t stringtosend[5] = "feta\n";

int main() {
	/*	At this stage the microcontroller clock setting is already configured, 
      this is done through SystemInit() function which is called from startup
      file (startup_stm32l0xx.s) before to branch to application main.
      To reconfigure the default setting of SystemInit() function, refer to
      system_stm32l0xx.c file */

	SystemConfig();

	while(1){
		
//		USART2->TDR = 'x';
//		while((USART2->ISR & USART_ISR_TC) != USART_ISR_TC);
//		USART2->ICR = USART_ICR_TCCF;
	}
}

void EXTI4_15_IRQHandler(void)
{
  if((EXTI->PR & EXTI_PR_PIF13) == EXTI_PR_PIF13)
  {
    /* Clear EXTI 0 flag */
    EXTI->PR = EXTI_PR_PIF13;	
    /* start USART transmission */
    USART2->TDR = stringtosend[send++]; /* Will inititiate TC if TXE */
  }
}

void USART2_IRQHandler(void)
{
  if((USART2->ISR & USART_ISR_TC) == USART_ISR_TC)
  {
    if(send == sizeof(stringtosend))
    {
      send=0;
      USART2->ICR = USART_ICR_TCCF; /* Clear transfer complete flag */
      LED_Toggle(); /* Toggle green led on PA5 */
    }
    else
    {
      /* clear transfer complete flag and fill TDR with a new char */
      USART2->TDR = stringtosend[send++];
    }
  }	
}


