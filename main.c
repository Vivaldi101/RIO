#include "rio.h"

#define array_count(a) sizeof(a) / sizeof(*a)

int main()
{
	raw_device_id_t id_usb = lookup_device_id(Device_usb);
	raw_device_id_t id_bluetooth = lookup_device_id(Device_bluetooth);

	char buffer[4096] = {0};
	const size_t size = 10;
	const size_t offset = 0;

	//for (size_t i = 0; i < 10; ++i)
	{
		write_device(&id_bluetooth, offset, size, array_count(buffer), buffer);
		read_device(&id_bluetooth, offset+8, size, array_count(buffer), buffer);
	}

	return 0;
}