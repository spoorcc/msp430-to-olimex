#include <msp430.h>

#include "USCI_A_to_UART.h"
#include "USCI_B_to_OLIMEX.h"

#define LED  BIT0 //Pin 1.0

#define RX_BUF_LENGTH 32
fifo_t rx_fifo;
