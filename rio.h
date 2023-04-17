#ifndef RIO_H
#define RIO_H

#include <stdlib.h>

typedef struct raw_device_request_t raw_device_request_t;
typedef struct raw_device_result_t raw_device_result_t;
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

typedef struct raw_device_id_t
{
	u32 ID;
} raw_device_id_t;

__declspec(align(64))	// Align to cache line.
typedef struct raw_device_request_t
{
	size_t offset;
	size_t size;
	void *buffer;
	raw_device_operation_t op;
	raw_device_id_t device;
} raw_device_request_t;

__declspec(align(64))	// Align to cache line.
typedef struct raw_device_result_t
{
	u32 error_code;
} raw_device_result_t;

raw_device_id_t lookup_device_id(const char* name);
const char* lookup_device_name(raw_device_id_t rdi);

void read_device(raw_device_id_t device, size_t offset, size_t size, char* buf);
void write_device(raw_device_id_t device, size_t offset, size_t size, char* buf);
typedef void raw_device_handler(raw_device_id_t instance, raw_device_request_t *packet, raw_device_result_t *result);

// Usb driver handler.
raw_device_handler usb_handler;

// Bluetooth driver handler.
raw_device_handler bluetooth_handler;

#endif
