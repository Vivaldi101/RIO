#include "rio.h"

#include <stdio.h>
#include <assert.h>

static void read_usb(raw_device_request_t *packet)
{
	assert(packet);
	printf("Reading %zu bytes from usb device at offset: %zu\n", packet->size, packet->offset); 

	const size_t size = packet->size;
	char* begin = (char*)packet->buffer + packet->offset;

	for (size_t i = 0; i < size; ++i)
	{
		//putc(begin[i], stdout);
	}
	puts("\n");
}

static void write_usb(raw_device_request_t *packet)
{
	assert(packet);
	printf("Writing %zu bytes to usb device at offset: %zu\n", packet->size, packet->offset); 

	const size_t size = packet->size;
	char* begin = (char*)packet->buffer + packet->offset;

	for (size_t i = 0; i < size; ++i)
	{
		begin[i] = 'W';
	}
}

void usb_handler(raw_device_request_t *packet)
{
	assert(packet);

	switch(packet->op)
	{
		switch_label RIO_read:
			read_usb(packet);
		switch_label RIO_write:
			write_usb(packet);
	}
}
