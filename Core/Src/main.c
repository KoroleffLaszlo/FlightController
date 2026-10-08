#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#include "stm32h753xx.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define _delay 10000000U

void delay(volatile uint32_t count)
{
	while (count--)
	{
		__asm volatile("nop");
	}
}

int main(void)
{
	RCC->AHB4ENR |= (0x1U << 4);

	// clearing then enabling to output
	GPIOE->MODER &= ~(0x3U << 2);
	GPIOE->MODER |= (0x1U << 2);

	while(1){

		//GPIOE->ODR |= 0x00000002; // LED ON
		GPIOE->ODR |= (0x1U << 1);

		delay(_delay);

		//GPIOE->ODR &= ~0x00000002; // LED OFF
		GPIOE->ODR &= ~(0x2U);

		delay(_delay);
	}

	/*
	 * enable the AH4B bus for pin
	 * enable mode for gpio
	 * enable type DEFAULT pushpull
	 * enable speed of register
	 *
	 */

}
