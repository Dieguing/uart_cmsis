#include "sysconfig.h"
#include "stm32l0xx.h"

int main() {

	SystemConfig();

	while(1){
		/* Turn on the LED */
		LED_ON();
		_delay();
		_delay();
		LED_OFF();
		_delay();
		_delay();
	}
}
