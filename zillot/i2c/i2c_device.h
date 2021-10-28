#ifndef ZILLOT_I2C_i2c_bus_device_H
#define ZILLOT_I2C_i2c_bus_device_H

#include <stdint.h>
#include <igris/compiler.h>
#include <igris/sync/semaphore.h>

struct i2c_bus_device;

struct i2c_bus_device_operations
{
	int (*write_memory)(
	    struct i2c_bus_device *,
	    uint8_t devaddr,
	    uint8_t memaddr,
	    const void * buffer, int buflen);


	int (*write)(
	    struct i2c_bus_device *,
	    uint8_t devaddr,
	    const void * buffer, int buflen);

	int (*read)(
	    struct i2c_bus_device *,
	    uint8_t devaddr,
	    const void * buffer, int buflen);

	void (*lock_bus)(struct i2c_bus_device *);
	void (*unlock_bus)(struct i2c_bus_device *);
};

struct i2c_bus_device
{
	const struct i2c_bus_device_operations * ops;
	sem_t sem;
};

__BEGIN_DECLS

int i2c_writeread(
    struct i2c_bus_device *,
    uint8_t devaddr,
    const void * wbuf, int wlen,
    void * rbuf, int rlen);

__END_DECLS

#endif