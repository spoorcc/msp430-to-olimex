CC=msp430-elf-gcc
CFLAGS=-Os -Wall -Wextra -pedantic -g -mmcu=msp430g2553

all :	main.o USCI_A_to_UART.o USCI_B_to_OLIMEX.o fifo.o
			$(CC) $(CFLAGS) -o main.elf main.o USCI_A_to_UART.o USCI_B_to_OLIMEX.o fifo.o         

# Rules for the separate objects
main.o :	main.c main.h
				$(CC) $(CFLAGS) -c main.c
				
USCI_A_to_UART.o :		USCI_A_to_UART.c USCI_A_to_UART.h fifo.h USCI_B_to_OLIMEX.h
							$(CC) $(CFLAGS) -c USCI_A_to_UART.c				
				
USCI_B_to_OLIMEX.o :	USCI_B_to_OLIMEX.c USCI_B_to_OLIMEX.h fifo.h
							$(CC) $(CFLAGS) -c USCI_B_to_OLIMEX.c							
							
fifo.o :	fifo.c fifo.h
				$(CC) $(CFLAGS) -c fifo.c
							
#Rule for cleaning
clean :		
		rm -fr main.elf main.o USCI_A_to_UART.o USCI_B_to_OLIMEX.o fifo.o

