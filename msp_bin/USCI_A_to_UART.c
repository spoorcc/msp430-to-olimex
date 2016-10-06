#include "USCI_A_to_UART.h"

void initUSCI_A_to_UART()
{	
	//Configure pins
	P1SEL  |= RXD + TXD;                       
  	P1SEL2 |= RXD + TXD;                       
  	
  	UCA0CTL1 |= UCSWRST;                      // Hold USCI in reset for configuration
  	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  	UCA0BR0 = 104;                            // 1MHz 9600
  	UCA0BR1 = 0;                              // 1MHz 9600
  	UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  	UCA0CTL1 &= ~UCSWRST;                     // Initialize USCI state machine
  	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{				
	if( IFG2 & UCA0RXIFG ){ //If USCI_A receives a message
			
		P1OUT ^= BIT0;	//Toggle led on pin1.0	
						 
		char received = UCA0RXBUF;
		
		if( received == ' ' ){
			//__bic_SR_register(LPM0_bits);; // wake up from low power mode
			fillTxBuff();
			
		}else{
			//Store the received char
			fifo_write( &rx_fifo, &received, 1);
		}
	}
}
	
