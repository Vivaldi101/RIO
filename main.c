#include "rio.h"
#include <stdio.h>

int main()
{
#define array_count(a) sizeof(a) / sizeof(*a)
#define buffer_size 4096

	raw_device_id_t id_usb = lookup_device_id(Device_usb);
	raw_device_id_t id_bluetooth = lookup_device_id(Device_bluetooth);

	char bluetooth_buffer[buffer_size] = {0};
	char usb_buffer[buffer_size] = {0};
	const size_t size = 20;
	const size_t offset = 10;

	printf("Starting devices...\n"); 
	for (size_t i = 0; i < 256; ++i)
	{
		write_device(&id_bluetooth, offset + 0, size, array_count(bluetooth_buffer), bluetooth_buffer);
		read_device(&id_bluetooth, offset + 0, size, array_count(bluetooth_buffer), bluetooth_buffer);

		write_device(&id_usb, offset + 0, size, array_count(usb_buffer), usb_buffer);
		read_device(&id_usb, offset + 0, size, array_count(usb_buffer), usb_buffer);
	}

	return 0;
}