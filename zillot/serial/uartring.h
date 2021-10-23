#ifndef GENOS_DATASTRUCT_UARTRING_H
#define GENOS_DATASTRUCT_UARTRING_H

#include <zillot/serial/uart.h>
#include <zillot/cdev.h>

#include <igris/sync/semaphore.h>
#include <igris/datastruct/dlist.h>
#include <igris/datastruct/ring.h>

typedef struct uartring_s
{
	struct char_device_s cdev;
	uart_s * udev;

	sem_t rxsem;
	sem_t txsem;
	
	char* rxbuffer;
	char* txbuffer;
	struct ring_head rxring;
	struct ring_head txring;
} uartring_s;

void uartring_init(
	uartring_s * uring, 
	uart_s * uart, 
	void* rxbuf, unsigned int rxsize,
	void* txbuf, unsigned int txsize);




/*	uartring(const char* name, genos::uart * udev,
	         char* rxbuffer, char* txbuffer,
	         size_t rxsz, size_t txsz)
		:
		genos::char_device(name),
		udev(udev), rxbuffer(rxbuffer), txbuffer(txbuffer),
		rxring(RING_HEAD_INIT(rxsz)), txring(RING_HEAD_INIT(txsz))
	{}

	uartring(const char* name, genos::uart * udev,
	         igris::buffer rxbuf, igris::buffer txbuf)
		:
		genos::char_device(name),
		udev(udev), rxbuffer(rxbuf.data()), txbuffer(txbuf.data()),
		rxring(RING_HEAD_INIT(rxbuf.size())), txring(RING_HEAD_INIT(txbuf.size()))
	{}

	int read(void* data, size_t size, int flags) override;
	int write(const void* data, size_t size, int flags) override;
	int release() override;
	int open(genos::openres * filp) override;

	size_t room() override;
	size_t avail() override;

	void begin(genos::uart * udev);
	void begin() { begin(udev); };
	void clear();*/

__BEGIN_DECLS

__END_DECLS

#define UARTRING_DECLARE(name, cname, uart, rxsz, txsz)				 			\
char name##_rxbuffer[rxsz];						 					 			\
char name##_txbuffer[txsz];						 					 			\
genos::uartring name { cname, (struct uart_device*)uart,					\
				name##_rxbuffer, name##_txbuffer,					 			\
				rxsz, txsz}

#endif