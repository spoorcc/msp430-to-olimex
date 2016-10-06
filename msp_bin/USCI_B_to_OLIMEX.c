#include "USCI_B_to_OLIMEX.h"

void initUSCI_B_to_OLIMEX()
{
	currentCol = 0x00;	
	
	//Set the clock to 1 MHz
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL  = CALDCO_1MHZ;
  
	//Enable the latch
	P2OUT |= SPI_LATCH;
	P2DIR |= SPI_LATCH;                
  	
	P2OUT &= ~SPI_LATCH;
		  
	//Setup SPI pins of USCI_B
	P1SEL  |= SPI_CLK + SPI_DATA;
	P1SEL2 |= SPI_CLK + SPI_DATA;
	
	//Set the USCI in reset to configure
	UCB0CTL1 |= UCSWRST;
  
	UCB0CTL0 |= UCCKPH + UCMST + UCSYNC;    // 3-pin, 8-bit SPI master
	UCB0CTL0 &= ~UCMSB;  					// LSB - first
	UCB0CTL1 |= UCSSEL_2;                   // SMCLK
	UCB0BR0  |= 0x02;                       // /2
	UCB0BR1  = 0;                           //
	UCB0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
	IE2 |= UCB0TXIE;                        // Enable USCI0 TX interrupt
	
	char buf[8] = { 0x03, 0x03, 0x0C, 0x0C, 0x30, 0x30, 0xC0, 0xC0 };
	fifo_write( &rx_fifo, &buf, 8);
}

void pulseLatch()
{
	P2OUT |= SPI_LATCH;
	__delay_cycles(10);
	P2OUT &= ~SPI_LATCH;
}

void fillTxBuff()
{
	char buf[8];
	int i ;
	int nBytesRead = fifo_read( &rx_fifo, &buf, 8);
				
	if( nBytesRead == 8)
	{
		for( i = 0; i < 8; i++ )
		{
			ledArray[i] = buf[i];
		}		
	}
	P1OUT ^= BIT0;
	while (!(IFG2 & UCB0TXIFG));
	UCB0TXBUF = 0x01;
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIB0TX_ISR(void)
{	
	P1OUT ^= BIT0;	//Toggle led on pin1.0	
			
	while (!(IFG2 & UCB0TXIFG));   // USCI_B0 TX buffer ready?
	//UCB0TXBUF = ledArray[ currentCol ];
	UCB0TXBUF = 0x01 /*<< currentCol*/;
	
	while (!(IFG2 & UCB0TXIFG));   // USCI_B0 TX buffer ready?
	UCB0TXBUF = 0x01 /*<< currentCol*/;
	
	currentCol++;
	currentCol = currentCol%8;
			
	__delay_cycles(50);
	pulseLatch();
	__delay_cycles(5000000);
}

