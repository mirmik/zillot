#ifndef GENOS_DRIVERS_I2C_DEVICE_H
#define GENOS_DRIVERS_I2C_DEVICE_H

#include <stdint.h>

struct i2c_device_operations
{
	int (*write_memory)(
	    uint8_t devaddr,
	    uint8_t memaddr,
	    const void * buffer, int buflen);


	int (*write)(
	    uint8_t devaddr,
	    const void * buffer, int buflen);

	int (*read)(
	    uint8_t devaddr,
	    const void * buffer, int buflen);

	void (*lock_bus)();
	void (*unlock_bus)();
};

struct i2c_device
{
	const i2c_device_operations * ops;
};

#endif