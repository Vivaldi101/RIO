#include "rio.h"
#include <stdio.h>

static void read_usb(raw_device_id_t* device, raw_device_request_t *packet, raw_device_result_t *result)
{
	printf("Reading %zu bytes from device: %s at offset: %zu\n", packet->size, lookup_device_name(device), packet->offset); 

	const size_t size = packet->size;
	char* begin = (char*)packet->buffer + packet->offset;

	for (size_t i = 0; i < size; ++i)
	{
		begin[i] = 'R';
	}
}

static void write_usb(raw_device_id_t* device, raw_device_request_t *packet, raw_device_result_t *result)
{
	printf("Writing %zu bytes to device: %s at offset: %zu\n", packet->size, lookup_device_name(device), packet->offset); 

	const size_t size = packet->size;
	char* begin = (char*)packet->buffer + packet->offset;

	for (size_t i = 0; i < size; ++i)
	{
		begin[i] = 'W';
	}
}

void usb_handler(raw_device_id_t* device, raw_device_request_t *packet, raw_device_result_t *result)
{
	switch(packet->op)
	{
		case RIO_read:
			read_usb(device, packet, result);
			result->error_code = 1; break;
		
		case RIO_write:
			write_usb(device, packet, result);
			result->error_code = 1; break;
		
		case RIO_get_name:
			puts("Getting device name..."); 
			result->error_code = 1; break;
		
		default: result->error_code = 0; break;
	}
}
