#include <stdio.h>
#include "u_ringbuf.h"

#define SIZE 3
void ui4_enable_all_log(void){
	
	return;
}

int main(int argc, const char *argv[])
{

	int i= 0;
	char array_test[SIZE][8] ={"123456","234567","345678"};
	RINGBUF_H h_ringbuf;

	h_ringbuf = u_ringbuf_malloc(1024); 
	if (NULL == h_ringbuf)
	{   
		printf("ringbuf malloc failed!\n");
		return -1;
	}  


	//INT32 u_ringbuf_write(RINGBUF_H handle, VOID *p_data, UINT32 ui4_size)
	for( i = 0;i < SIZE;i++){
		u_ringbuf_write(h_ringbuf,array_test[i], 8);
	}

	char tmp[8] = {0};

	u_ringbuf_read(h_ringbuf,tmp, 8);
	printf("%s\n",tmp);
	u_ringbuf_read(h_ringbuf,tmp, 8);
	printf("%s\n",tmp);
	u_ringbuf_read(h_ringbuf,tmp, 8);
	printf("%s\n",tmp);
	for( i = 0;i < 8;i++){
		tmp[i] = 0;
	}
	u_ringbuf_read(h_ringbuf,tmp, 8);
	printf("%s\n",tmp);



	return 0;
}
