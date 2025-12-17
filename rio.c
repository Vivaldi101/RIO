#include "rio.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>

typedef struct raw_device_t
{
	raw_device_handler *handler;
} raw_device_t;

static void jump_to_device_handler(raw_device_request_t* packet)
{
	assert(packet);

	size_t running_offset = packet->offset;
	for(unsigned i = 0; i < array_count(device_ids); ++i)
	{
      raw_device_id_t device = device_ids[i];
		packet->offset = running_offset;

		if(packet->offset + packet->size > packet->max_size)
		{
         printf("packet offset + size overflows max_size for device: %u\n", device.ID);
         continue;
      }

		assert(packet->offset + packet->size <= packet->max_size);

      switch(device.ID)
      {
         case Device_usb:
			   usb_handler(packet);
         break;
         case Device_bluetooth:
            bluetooth_handler(packet);
         break;
         default:
            invalid;
      }

		running_offset += (packet->offset + packet->size);
	}
}

void read_devices(size_t offset, size_t size, size_t max_size, char* buffer)
{
	if (!buffer)
		return;
	if (offset >= max_size)
		return;
	if (size > max_size - offset)
		return;
	raw_device_request_t packet = {.buffer = buffer, .offset = offset, .op = RIO_read, .size = size, .max_size = max_size};

	jump_to_device_handler(&packet);
}

void write_devices(size_t offset, size_t size, size_t max_size, char* buffer)
{
	if (!buffer)
		return;
	if (offset >= max_size)
		return;
	if (size > max_size - offset)
		return;
	raw_device_request_t packet = {.buffer = buffer, .offset = offset, .op = RIO_write, .size = size, .max_size = max_size};

	jump_to_device_handler(&packet);
}
