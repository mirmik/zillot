#ifndef ZILLOT_SERIAL_UARTRING_H
#define ZILLOT_SERIAL_UARTRING_H

#include <sys/cdefs.h>
#include <zillot/common/chardev.h>
#include <zillot/common/uart.h>
#include <igris/buffer.h>
#include <igris/datastruct/dlist.h>
#include <igris/datastruct/ring.h>

namespace zillot
{
	class uartring : public zillot::chardev
	{
		zillot::uart * udev = nullptr;
		char* rxbuffer = nullptr;
		char* txbuffer = nullptr;
		struct ring_head rxring;
		struct ring_head txring;
		struct dlist_head txwait = DLIST_HEAD_INIT(txwait);
		struct dlist_head rxwait = DLIST_HEAD_INIT(rxwait);
		int refs = 0;

	public:
		uartring(
			zillot::uart * udev,
		    igris::buffer rxbuf, 
		    igris::buffer txbuf
		)
			:
			zillot::chardev(),
			udev(udev), 
			rxbuffer(rxbuf.data()), 
			txbuffer(txbuf.data()),
			rxring(RING_HEAD_INIT((unsigned int)rxbuf.size())), 
			txring(RING_HEAD_INIT((unsigned int)txbuf.size()))
		{}

		uartring(const uartring&) = delete;
		uartring& operator=(const uartring&) = delete;

		int read(void* data, size_t size) override;
		int write(const void* data, size_t size) override;
		int release() override;
		int open(void * controller_id) override;

		size_t room() override;
		size_t avail() override;

		void begin(zillot::uart * udev);
		void begin() { begin(udev); };
		void clear();

		static void uartring_irq_handler(void* priv, int code);
	};
}

#endif