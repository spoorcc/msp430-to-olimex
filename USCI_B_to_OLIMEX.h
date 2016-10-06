#ifndef USCI_B_TO_OLIMEX_H
#define USCI_B_TO_OLIMEX_H

#include "fifo.h"
#include <msp430.h>

#define SPI_LATCH   BIT0  //Pin 2.0
#define SPI_DATA    BIT7  //Pin 1.7
#define SPI_DATA_IN BIT6  //Pin 1.6
#define SPI_CLK     BIT5  //Pin 1.5

extern fifo_t rx_fifo;

volatile unsigned char ledArray[8]; 	
volatile unsigned char currentCol;

//---- methods

void initUSCI_B_to_OLIMEX();
void pulseLatch();

void fillTxBuff();

#endif //USCI_B_TO_OLIMEX_H
