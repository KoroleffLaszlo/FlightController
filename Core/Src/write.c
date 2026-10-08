#include <write.h>
#include "stm32h753xx.h"

bool UART_init()
{


	/*
	 * UART_Init()
	    │
	    ├── 1. Enable GPIO peripheral clock

	    		enable PD8 and PD9 pins
	    		enable APB1 bus for USART3
	    			--- APB1 enable page from RM
	    			--- set PD8 and PD9 to alternate function registers
	    				--- set to AFR[1] for higher ports then use 0x7 and bit shift appropriately

	    │
	    ├── 2. Configure TX/RX pins
	    │       ├── MODER → Alternate Function
	    │       ├── AFR   → Select USART function
	    │       ├── OTYPER
	    │       ├── OSPEEDR
	    │       └── PUPDR
	    │
	    ├── 3. Enable USART peripheral clock
	    │
	    ├── 4. Configure USART
	    │       ├── Baud rate
	    │       ├── Word length
	    │       ├── Stop bits
	    │       ├── Parity
	    │       └── TX/RX enable
	    │
	    ├── 5. Enable USART
	    │
	    └── 6. Verify configuration
	            ↓
	        return true/false
	 */
	RCC->AHB4ENR |= (0x1U << 3);
	RCC->APB1LENR |= (0x1U << 18);

	// PD8 setup
	GPIOD->MODER &= ~(0x3U << 16);
	GPIOD->MODER |= (0x2U << 16);

	// PD9 setup
	GPIOD->MODER &= ~(0x3U << 18);
	GPIOD->MODER |= (0x2U << 18);

	// set pins to alternate function registers
	// high registers from 8-15 so AFR[1]
	GPIOD->AFR[1] =
	GPIOD->AFR[1] =

}
