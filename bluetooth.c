#include "rio.h"
#include <stdio.h>

static void read_bluetooth(raw_device_id_t instance, raw_device_request_t *packet, raw_device_result_t *result)
{
	printf("Reading %u bytes from device: %s\n", packet->size, lookup_device_name(instance)); 
}

static void write_bluetooth(raw_device_id_t instance, raw_device_request_t *packet, raw_device_result_t *result)
{
	printf("Writing %u bytes to device: %s\n", packet->size, lookup_device_name(instance)); 
}

void bluetooth_handler(raw_device_id_t instance, raw_device_request_t *packet, raw_device_result_t *result)
{
	switch(packet->op)
	{
		case RIO_read:
			read_bluetooth(instance, packet, result);
			result->error_code = 1; break;
		
		case RIO_write:
			write_bluetooth(instance, packet, result);
			result->error_code = 1; break;
		
		case RIO_get_name:
			puts("Getting device name..."); 
			result->error_code = 1; break;
		
		default: result->error_code = 0; break;
	}
}

