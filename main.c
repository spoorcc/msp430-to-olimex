#include "main.h"

void main(void)
{
   //Stop watchdog timer
   WDTCTL = WDTPW + WDTHOLD;

   initUSCI_A_to_UART();
   initUSCI_B_to_OLIMEX();

   P1OUT |= LED;
   P1DIR |= LED;

   char rx_buf[RX_BUF_LENGTH];
   fifoInit( &rx_fifo, rx_buf, RX_BUF_LENGTH );

   __enable_interrupt();

   UCB0TXBUF = 0x01;
   fillTxBuff();

   P1OUT &= ~LED;

   while(1)
   {
      while (!(IFG2 & UCB0TXIFG));   // USCI_B0 TX buffer ready?
      UCB0TXBUF = ledArray[ currentCol ];

      while (!(IFG2 & UCB0TXIFG));   // USCI_B0 TX buffer ready?
      UCB0TXBUF = 0x01 << currentCol;

      currentCol++;
      currentCol = currentCol%8;

      __delay_cycles(50);
      pulseLatch();
   }

}
