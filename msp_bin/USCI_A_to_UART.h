#ifndef USCI_A_TO_UART_H
#define USCI_A_TO_UART_H

#include <msp430.h>

#include "fifo.h"
#include "USCI_B_to_OLIMEX.h"

#define RXD		BIT1  // Hardware UART on P1.1 & 1.2
#define TXD		BIT2  // Dont forget to turn the jumpers between emulation and programming to HW uart

extern fifo_t rx_fifo;

void initUSCI_A_to_UART();

#endif //USCI_A_TO_UART_H
