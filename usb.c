#include "rio.h"

#include <stdio.h>
#include <assert.h>

static void read_usb(raw_device_request_t *packet, raw_device_result_t *result)
{
	printf("Reading %zu bytes from usb device at offset: %zu\n", packet->size, packet->offset); 

	const size_t size = packet->size;
	char* begin = (char*)packet->buffer + packet->offset;

	for (size_t i = 0; i < size; ++i)
	{
		putc(begin[i], stdout);
	}
	puts("\n");
}

static void write_usb(raw_device_request_t *packet, raw_device_result_t *result)
{
	printf("Writing %zu bytes to usb device at offset: %zu\n", packet->size, packet->offset); 

	const size_t size = packet->size;
	char* begin = (char*)packet->buffer + packet->offset;

	for (size_t i = 0; i < size; ++i)
	{
		begin[i] = 'W';
	}
}

void usb_handler(raw_device_request_t *packet, raw_device_result_t *result)
{
	assert(packet);
	assert(result);

	switch(packet->op)
	{
		case RIO_read:
			read_usb(packet, result);
			result->error_code = 1; break;
		
		case RIO_write:
			write_usb(packet, result);
			result->error_code = 1; break;
		
		case RIO_get_name:
			puts("Getting device name..."); 
			result->error_code = 1; break;
		
		default: result->error_code = 0; break;
	}
}
