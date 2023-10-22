#include "rio.h"

#include <string.h>
#include <assert.h>

typedef struct raw_device_t
{
	raw_device_handler *handler;
} raw_device_t;

void null_handler(raw_device_id_t* device, raw_device_request_t *packet, raw_device_result_t *result)
{
}

raw_device_id_t lookup_device_id(device_id id)
{
	assert(id != Device_invalid);

	raw_device_id_t result = {.ID = Device_invalid};

	switch(id)
	{
	case Device_usb:
		result.ID = Device_usb;
		break;
	case Device_bluetooth:
		result.ID = Device_bluetooth;
		break;
	default:
		assert(0);
		break;
	}

	assert(result.ID != Device_invalid);

	return result;
}

const char* lookup_device_name(raw_device_id_t* device)
{
	assert(device->ID != Device_invalid);

	const char* result = NULL;

	switch(device->ID)
	{
	case Device_usb:
		result = "usb";
		break;
	case Device_bluetooth:
		result = "bluetooth";
		break;
	default:
		assert(0);
		break;
	}

	assert(result);

	return result;
}

static void jump_to_device_handler(raw_device_id_t* device, raw_device_request_t* packet, raw_device_result_t* result)
{
	switch(device->ID)
	{
	case Device_usb: 
		usb_handler(device, packet, result);
		break;
	case Device_bluetooth: 
		bluetooth_handler(device, packet, result);
		break;
	default:
		null_handler(device, packet, result);
		break;
	}
}

void read_device(raw_device_id_t* device, size_t offset, size_t size, char* buffer)
{
	raw_device_result_t result = {0};

	raw_device_request_t packet = 
	{
		.buffer = buffer, 
		.offset = offset, 
		.op = RIO_read, 
		.size = size
	};

	jump_to_device_handler(device, &packet, &result);

	// Do something with result...
}

void write_device(raw_device_id_t* device, size_t offset, size_t size, char* buffer)
{
	raw_device_result_t result = {0};

	raw_device_request_t packet = 
	{
		.buffer = buffer, 
		.offset = offset, 
		.op = RIO_write, 
		.size = size
	};

	jump_to_device_handler(device, &packet, &result);

	// Do something with result...
}
