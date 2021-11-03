#ifndef ZILLOT_CHAR_DEVICE_H
#define ZILLOT_CHAR_DEVICE_H

#include <assert.h>
#include <igris/compiler.h>
#include <stddef.h>

struct char_device_s;

typedef struct char_device_operation_s
{
    int (*write)(struct char_device_s *dev, const void *data, unsigned int dlen,
                 uint8_t flags);
    int (*read)(struct char_device_s *dev, void *data, unsigned int dlen,
                uint8_t flags);
    int (*avail)(struct char_device_s *dev);
    int (*room)(struct char_device_s *dev);
} char_device_operation_s;

typedef struct char_device_s
{
    const char_device_operation_s *c_ops;
} char_device_s;

__BEGIN_DECLS

static inline int cdev_avail(struct char_device_s *dev)
{
    return dev->c_ops->avail(dev);
}

static inline int cdev_room(struct char_device_s *dev)
{
    return dev->c_ops->room(dev);
}

static inline int cdev_write(struct char_device_s *dev, const void *data,
                             unsigned int dlen, uint8_t flags)
{
    return dev->c_ops->write(dev, data, dlen, flags);
}

static inline int cdev_read(struct char_device_s *dev, void *data,
                            unsigned int dlen, uint8_t flags)
{
    return dev->c_ops->read(dev, data, dlen, flags);
}

__END_DECLS

#define CHAR_DEVICE_INIT(name, ops)                                            \
    {                                                                          \
        .c_ops = ops                                                           \
    }

#endif