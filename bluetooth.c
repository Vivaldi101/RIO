#include "rio.h"
#include <stdio.h>

#include <assert.h>

static void read_bluetooth(raw_device_request_t *packet)
{
	assert(packet);
	printf("Reading %zu bytes from bluetooth device at offset: %zu\n", packet->size, packet->offset); 

	const size_t size = packet->size;
	char* begin = (char*)packet->buffer + packet->offset;

	for (size_t i = 0; i < size; ++i)
	{
		putc(begin[i], stdout);
	}
	puts("\n");
}

static void write_bluetooth(raw_device_request_t *packet)
{
	assert(packet);
	printf("Writing %zu bytes to bluetooth device at offset: %zu\n", packet->size, packet->offset); 

	const size_t size = packet->size;
	char* begin = (char*)packet->buffer + packet->offset;

	for (size_t i = 0; i < size; ++i)
	{
		begin[i] = 'W';
	}
}

void bluetooth_handler(raw_device_request_t *packet)
{
	assert(packet);

	switch(packet->op)
	{
		case RIO_read:
			read_bluetooth(packet);
		
		case RIO_write:
			write_bluetooth(packet);
		
		case RIO_get_name:
			puts("Getting device name..."); 
		
		default: break;
	}
}

