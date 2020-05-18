#ifndef _SysConfig_H

#define LED_PIN 5
#define LED_ON() GPIOA->BSRR |= (1 << LED_PIN)
#define LED_OFF() GPIOA->BRR |= (1 << LED_PIN)
#define LED_Toggle() GPIOA->ODR ^= (1 << LED_PIN)
#define VALUE 100

extern void SystemConfig(void);
extern void _delay(void);

#endif
