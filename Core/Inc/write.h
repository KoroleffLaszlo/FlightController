#ifndef INC_WRITE_H_
#define INC_WRITE_H_



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

bool UART_Init();


#endif /* INC_WRITE_H_ */
