#include "rio.h"
#include <string.h>

enum 
{
	Device_invalid,
	Device_usb,
	Device_bluetooth
};

typedef struct raw_device_t
{
	raw_device_handler *handler;
} raw_device_t;

static raw_device_t raw_device;

raw_device_id_t lookup_device_id(const char* name)
{
	raw_device_id_t rdi = {0};

	if (strcmp(name, "usb") == 0)
	{
		rdi.ID = Device_usb;
	}
	else if (strcmp(name, "bluetooth") == 0)
	{
		rdi.ID = Device_bluetooth;
	}

	return rdi;
}

const char* lookup_device_name(raw_device_id_t rdi)
{
	const char* name = NULL;

	switch(rdi.ID)
	{
	case Device_usb:
		name = "usb";
		break;
	case Device_bluetooth:
		name = "bluetooth";
		break;
	default:
		break;
	}

	return name;
}

static void set_device_handler(raw_device_id_t device)
{
	switch(device.ID)
	{
	case Device_usb: 
		raw_device.handler = usb_handler;
		break;
	case Device_bluetooth: 
		raw_device.handler = bluetooth_handler;
		break;
	default: raw_device.handler = NULL;
		break;
	}
}

static void set_packet(raw_device_request_t* packet, raw_device_id_t device, size_t offset, size_t size)
{
	packet->size = size;
	packet->offset = offset;
	packet->device = device;
}

void read_device(raw_device_id_t device, size_t offset, size_t size, char* buf)
{
	raw_device_result_t result = {0};

	raw_device_request_t packet = {0};
	packet.op = RIO_read;
	set_packet(&packet, device, offset, size);

	set_device_handler(device);

	raw_device.handler(device, &packet, &result);

	// Do something with result...
}

void write_device(raw_device_id_t device, size_t offset, size_t size, char* buf)
{
	raw_device_result_t result = {0};

	raw_device_request_t packet = {0};
	packet.op = RIO_write;
	set_packet(&packet, device, offset, size);

	set_device_handler(device);

	raw_device.handler(device, &packet, &result);

	// Do something with result...
}
