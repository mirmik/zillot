#ifndef ZILLOT_CHAR_DEVICE_H
#define ZILLOT_CHAR_DEVICE_H

#include <igris/util/numconvert.h>

namespace zillot 
{
	class chardev
	{
	protected:
		uint16_t flags = 0;

	public:
		chardev() {} 

		int print(int32_t arg);

		virtual int read(void* data, size_t size) = 0;
		virtual int write(const void* data, size_t size) = 0;
		virtual int release() = 0;
		virtual int open(void * controller_id) = 0;
		virtual size_t room() = 0;
		virtual size_t avail() = 0;

        void set_flag(uint16_t flags) 
        {
        	this->flags = flags;
        }

        virtual ~chardev() = default;
	};
}

#endif