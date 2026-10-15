#include <write.h>
#include "stm32h753xx.h"

#define UART_BAUD_RATE 115200U
#define DEFAULT_KERNEL_FREQ_HZ 64000000U

bool UART3_Init(uint32_t kernel_clk_hz)
{
	RCC->AHB4ENR |= (0x1U << 3);
	RCC->APB1LENR |= RCC_APB1LEND_USART3EN; // enable uart clock

	// PD8 PD9 setup
	GPIOD->MODER &= ~((0x3U << 16) | (0x3U << 18)); // clearing bits
	GPIOD->MODER |= ((0x2U << 16) | (0x2U << 18));


	// set pins to alternate function registers
	// high registers from 8-15 so AFR[1]
	GPIOD->AFR[1] &= ~((0xFU << 0) | (0xFU << 4));
	GPIOD->AFR[1] |= ((0x7U << 0) | (0x7U << 4));

	// setting TX to push/pull PD8
	GPIOD->OTYPER = ~(0x1U << 8);

	// setting output speed
	GPIOD->OSPEEDR &= ~((0x3U << 16) | (0x3U << 18));
	GPIOD->OSPEEDR |= ((0x1U << 16) | (0x1U << 18));

	// setting RX to pull-up (high when idle) PD9
	GPIOD->PUPDR &= ~(0x3U << 18);
	GPIOD->PUPDR |= (0x1U << 18);

	// setting up control registers for UART3
	USART3->CR1 &= ~USART_CR1_UE;

	USART3->CR1 = 0;
	USART3->CR2 = 0;
	USART3->CR3 = 0;

	// config baud rate
	USART3->BRR =
			(kernel_clk_hz + UART_BAUD_RATE / 2U)
			/ UART_BAUD_RATE;

	// enable transmission and receiver
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;


	USART3->CR1 |= USART_CR1_UE;

	// verifying start up with interrupt and status registers
	// TODO: add polling for timeouts
	while (!(USART3->ISR & USART_ISR_TEACK)) {}

	while (!(USART3->ISR & USART_ISR_REACK)) {}

	return true;
}


uint32_t UART3_GetClockSource(void)
{
	return RCC->D2CCIP2R & 0x7U;

}
