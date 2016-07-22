/*
 * main.cc
 *
 *  Created on: Jul 22, 2016
 *      Author: erlkoenig
 */

#include <cstdint>
#include <stm32l1xx.h>

/*
 * User LD3: Green user LED connected to the I/O PC9 of the STM32L100RCT6.
• User LD4: Blue user LED connected to the I/O PC8 of the STM32L100RCT6.
 */

extern "C" void mysleep (uint32_t cycles);

void initRamCode () {
	extern uint32_t _sramcode, _eramcode, _siramcode;

	for (uint32_t* dest = &_sramcode, *src = &_siramcode; dest != &_eramcode; ++dest, ++src) {
		*dest = *src;
	}
}

int main () {

	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	asm volatile ("dsb");
	initRamCode ();

	SYSCFG->MEMRMP = 3;

	GPIOC->MODER = GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;
	GPIOC->OSPEEDR = GPIO_OSPEEDER_OSPEEDR8_0 | GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_0 | GPIO_OSPEEDER_OSPEEDR9_1;

	while (1) {
		GPIOC->BSRRL = GPIO_BSRR_BS_8;
		GPIOC->BSRRH = GPIO_BSRR_BS_9;
		mysleep (1000000);
		GPIOC->BSRRH = GPIO_BSRR_BS_8;
		GPIOC->BSRRL = GPIO_BSRR_BS_9;
		mysleep (1000000);
	}
}
