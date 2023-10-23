#include "rio.h"

#include <string.h>
#include <assert.h>

typedef struct raw_device_t
{
	raw_device_handler *handler;
} raw_device_t;

static void null_handler(raw_device_id_t* device, raw_device_request_t *packet, raw_device_result_t *result)
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

static raw_device_result_t jump_to_device_handler(raw_device_id_t* device, raw_device_request_t* packet)
{
	raw_device_result_t result = {0};

	switch(device->ID)
	{
	case Device_usb: 
		usb_handler(device, packet, &result);
		break;
	case Device_bluetooth: 
		bluetooth_handler(device, packet, &result);
		break;
	default:
		null_handler(device, packet, &result);
		break;
	}

	return result;
}

static raw_device_request_t make_packet(size_t offset, size_t size, size_t max_size, char* buffer, raw_device_operation_t op)
{
	assert(offset < max_size);
	assert(size <= max_size - offset);
	assert(buffer);

	raw_device_request_t packet = 
	{
		.buffer = buffer, 
		.offset = offset, 
		.op = op, 
		.size = size
	};

	return packet;
}

void read_device(raw_device_id_t* device, size_t offset, size_t size, size_t max_size, char* buffer)
{
	if (!buffer || !device)
	{
		return;
	}
	if (offset >= max_size)
	{
		return;
	}
	if (size > max_size - offset)
	{
		return;
	}
	raw_device_request_t packet = make_packet(offset, size, max_size, buffer, RIO_read);

	raw_device_result_t result = jump_to_device_handler(device, &packet);

	// Do something with result...

	result.error_code;
}

void write_device(raw_device_id_t* device, size_t offset, size_t size, size_t max_size, char* buffer)
{
	if (!buffer || !device)
	{
		return;
	}
	if (offset >= max_size)
	{
		return;
	}
	if (size > max_size - offset)
	{
		return;
	}
	raw_device_request_t packet = make_packet(offset, size, max_size, buffer, RIO_write);

	raw_device_result_t result = jump_to_device_handler(device, &packet);

	// Do something with result...

	result.error_code;
}
