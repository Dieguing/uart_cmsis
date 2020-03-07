#ifndef _SysConfig_H

#define LED_PIN 5
#define LED_ON() GPIOA->BSRR |= (1 << LED_PIN)
#define LED_OFF() GPIOA->BRR |= (1 << LED_PIN)

extern void SystemConfig(void);
extern void _delay(void);

#endif
