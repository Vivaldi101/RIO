#include "rio.h"

#include <string.h>
#include <assert.h>

typedef struct raw_device_t
{
	raw_device_handler *handler;
} raw_device_t;

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

static void jump_to_device_handler(device_id id, raw_device_request_t* packet)
{
	assert(id == Device_bluetooth || id == Device_usb);
	assert(packet);

	switch(id)
	{
	case Device_usb: 
		usb_handler(packet);
		break;
	case Device_bluetooth: 
		bluetooth_handler(packet);
		break;
	default:
		assert(0);
		break;
	}
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

	jump_to_device_handler(device->ID, &packet);
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

	jump_to_device_handler(device->ID, &packet);
}
