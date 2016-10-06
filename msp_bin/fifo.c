#include "fifo.h"

void fifoInit( 	fifo_t* f, char* buf, int size )
{
	f->head = 0;
	f->tail = 0;
	f->size = size;
	f->buf = buf;
}

int fifo_read(	fifo_t* f, void* buf, int nbytes )
{
	int i;
	char* p;
	p = buf;
	
	for( i = 0; i < nbytes; i++){
		if(f->tail != f->head ){
			*p++ = f->buf[f->tail];
			
			f->tail++;
			
			if( f->tail == f->size){
				f->tail = 0;
			}
		}
		else{
			return i;
		}		
	}
	return nbytes;
}
				
int fifo_write(	fifo_t* f, const void* buf, int nbytes )
{
	int i;
	const char *p;
	p = buf;
	
	for( i=0; i <nbytes; i++ )
	{
		if( ( f->head + 1 == f->tail ) || 
				((f->head + 1 == f->size) && (f->tail == 0) ) )
		{
			return i;
		}
		else
		{
			f->buf[f->head] = *p++;
			f->head++;
			
			if( f->head == f->size){
				f->head = 0;
			}
		}
	}
	
	return nbytes;
}
