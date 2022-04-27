#ifndef ZILLOT_SERIAL_UARTRING_H
#define ZILLOT_SERIAL_UARTRING_H

#include <sys/cdefs.h>

#include <zillot/cdev.h>
#include <zillot/serial/uart.h>

#include <igris/buffer.h>
#include <igris/datastruct/dlist.h>
#include <igris/datastruct/ring.h>

namespace zillot
{

	struct uartring : public zillot::char_device
	{
		zillot::uart * udev;
		char* rxbuffer;
		char* txbuffer;
		struct ring_head rxring;
		struct ring_head txring;

		struct dlist_head txwait = DLIST_HEAD_INIT(txwait);
		struct dlist_head rxwait = DLIST_HEAD_INIT(rxwait);

		uint8_t debug_mode = 0;
		int refs = 0;

		uartring(const char* name, zillot::uart * udev,
		         char* rxbuffer, char* txbuffer,
		         size_t rxsz, size_t txsz)
			:
			zillot::char_device(name),
			udev(udev), rxbuffer(rxbuffer), txbuffer(txbuffer),
			rxring(RING_HEAD_INIT(rxsz)), txring(RING_HEAD_INIT(txsz))
		{}

		uartring(const char* name, zillot::uart * udev,
		         igris::buffer rxbuf, igris::buffer txbuf)
			:
			zillot::char_device(name),
			udev(udev), rxbuffer(rxbuf.data()), txbuffer(txbuf.data()),
			rxring(RING_HEAD_INIT(rxbuf.size())), txring(RING_HEAD_INIT(txbuf.size()))
		{}

		int read(void* data, size_t size, int flags) override;
		int write(const void* data, size_t size, int flags) override;
		int release() override;
		int open(zillot::openres * filp) override;

		size_t room() override;
		size_t avail() override;

		void begin(zillot::uart * udev);
		void begin() { begin(udev); };
		void clear();
	};
}

#define UARTRING_DECLARE(name, cname, uart, rxsz, txsz)				 			\
char name##_rxbuffer[rxsz];						 					 			\
char name##_txbuffer[txsz];						 					 			\
zillot::uartring name { cname, (struct uart_device*)uart,					\
				name##_rxbuffer, name##_txbuffer,					 			\
				rxsz, txsz}

#endif