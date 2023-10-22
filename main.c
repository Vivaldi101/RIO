#include "rio.h"

int main()
{
	raw_device_id_t id_usb = lookup_device_id(Device_usb);
	raw_device_id_t id_bluetooth = lookup_device_id(Device_bluetooth);

	char buffer[256] = {0};

	read_device(&id_usb, 3, 1, buffer);
	write_device(&id_usb, 1, 2, buffer);

	read_device(&id_bluetooth, 10, 3, buffer);
	write_device(&id_bluetooth, 4, 4, buffer);

	write_device(&id_bluetooth, 0, 1, buffer);

	return 0;
}