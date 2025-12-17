#include "rio.h"
#include <stdio.h>

int main()
{
   #define buffer_size 4096

   char device_buffer[buffer_size] = {0};

   size_t size = 20;
   size_t offset = 10;

   printf("Starting devices...\n\n");

   write_devices(offset + 0, size, array_count(device_buffer), device_buffer);
   read_devices(offset + 0, size, array_count(device_buffer), device_buffer);

   size += 20;
   offset += buffer_size; // invalid offset by design

   write_devices(offset + 0, size, array_count(device_buffer), device_buffer);
   read_devices(offset + 0, size, array_count(device_buffer), device_buffer);

   return 0;
}