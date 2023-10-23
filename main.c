#include "rio.h"

int main()
{
#define array_count(a) sizeof(a) / sizeof(*a)

	raw_device_id_t id_usb = lookup_device_id(Device_usb);
	raw_device_id_t id_bluetooth = lookup_device_id(Device_bluetooth);

	char bluetooth_buffer[4096] = {0};
	char usb_buffer[4096] = {'A', 'B'};
	const size_t size = 10;
	const size_t offset = 0;

	for (size_t i = 0; i < 5; ++i)
	{
		write_device(&id_bluetooth, offset + 0, size, array_count(bluetooth_buffer), bluetooth_buffer);
		read_device(&id_bluetooth, offset + 0, size, array_count(bluetooth_buffer), bluetooth_buffer);
		read_device(&id_usb, offset + 0, size, array_count(usb_buffer), usb_buffer);
	}

	return 0;
}