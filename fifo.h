#ifndef FIFO_H
#define FIFO_H

typedef struct{
	char* buf;
	int head;
	int tail;
	int size;
} fifo_t;

void fifoInit( 	fifo_t* f, 
				char* buf, 
				int size	);

int fifo_read(	fifo_t* f,
				void* buf,
				int nbytes	);
				
int fifo_write(	fifo_t* f,
				const void* buf,
				int nbytes );

#endif //FIFO_H
