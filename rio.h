#ifndef RIO_H
#define RIO_H

#include <stdlib.h>

// Move this into common header
#define halt abort();
#define pre(a) if(!(a)) halt
#define post(a) if(!(a)) halt
#define invariant(a) if(!(a)) halt
#define implies(a, b) (!(a) || (b))

#define invalid halt;

#define switch_label break; case
#define array_count(a) sizeof(a) / sizeof(*a)

typedef unsigned int u32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned long long u64;

typedef enum raw_device_operation_t
{
	RIO_none,
	
	RIO_read,
	RIO_write,
	RIO_get_name,
	
	RIO_private = 0x80000000,
} raw_device_operation_t;

typedef enum device_id
{
	#define X(name) name,
   X(Device_invalid)
	#include "device_list.def"
	#undef X
} device_id;

// Align to cache line.
#define cache_line_size 64

__declspec(align(cache_line_size))	
typedef struct raw_device_id_t
{
	device_id ID;
} raw_device_id_t;

__declspec(align(cache_line_size))
typedef struct raw_device_request_t
{
	size_t offset;
	size_t size;
	size_t max_size;
	void *buffer;
	raw_device_operation_t op;
} raw_device_request_t;

__declspec(align(cache_line_size))
typedef struct raw_device_result_t
{
	u32 error_code;
} raw_device_result_t;

raw_device_id_t lookup_device_id(device_id id);

void read_devices(size_t offset, size_t size, size_t max_size, char* buffer);
void write_devices(size_t offset, size_t size, size_t max_size, char* buffer);
typedef void raw_device_handler(raw_device_request_t *packet);

// Usb driver handler.
raw_device_handler usb_handler;
// Bluetooth driver handler.
raw_device_handler bluetooth_handler;
// All the devices
static raw_device_id_t device_ids[] =
{
#define X(name) name,
#include "device_list.def"
#undef X
};

#endif
