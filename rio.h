#ifndef RIO_H
#define RIO_H

#include <stdlib.h>

#define halt abort();

#define pre(a) if(!(a)) halt
#define post(a) if(!(a)) halt
#define invariant(a) if(!(a)) halt
#define implies(a, b) (!(a) || (b))

typedef unsigned int u32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned long long u64;
typedef u32 bool;

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
	Device_invalid,
	Device_usb,
	Device_bluetooth
} device_id;

typedef struct raw_device_id_t
{
	device_id ID;
} raw_device_id_t;

__declspec(align(64))	// Align to cache line.
typedef struct raw_device_request_t
{
	size_t offset;
	size_t size;
	void *buffer;
	raw_device_operation_t op;
} raw_device_request_t;

__declspec(align(64))	// Align to cache line.
typedef struct raw_device_result_t
{
	u32 error_code;
} raw_device_result_t;

const char* lookup_device_name(raw_device_id_t* rdi);
raw_device_id_t lookup_device_id(device_id id);

void read_device(raw_device_id_t* device, size_t offset, size_t size, size_t max_size, char* buffer);
void write_device(raw_device_id_t* device, size_t offset, size_t size, size_t max_size, char* buffer);
typedef void raw_device_handler(raw_device_id_t* device, raw_device_request_t *packet, raw_device_result_t *result);

// Usb driver handler.
raw_device_handler usb_handler;

// Bluetooth driver handler.
raw_device_handler bluetooth_handler;

// Null driver handler. Does nothing.
raw_device_handler null_handler;

#endif
