#include "rio.h"

int main()
{
	raw_device_id_t id = lookup_device_id("usb");

	char buffer[256];
	read_device(id, 0, 1, buffer);
	write_device(id, 0, 2, buffer);

	id = lookup_device_id("bluetooth");
	read_device(id, 0, 3, buffer);
	write_device(id, 0, 4, buffer);

	return 0;
}