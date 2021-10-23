#ifndef ZILLOT_CHAR_DEVICE_H
#define ZILLOT_CHAR_DEVICE_H

#include <igris/compiler.h>

struct char_device_s;

typedef struct char_device_operation_s 
{
	int (*write)(struct char_device_s* dev, void * data, int dlen);
	int (*read)(struct char_device_s* dev, void * data, int dlen);
	int (*avail)(struct char_device_s* dev);
	int (*room)(struct char_device_s* dev);
} char_device_operation_s;

typedef struct char_device_s 
{
	const char_device_operation_s c_ops;
} char_device_s;

#endif