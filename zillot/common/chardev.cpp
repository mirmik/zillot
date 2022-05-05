#include <zillot/common/chardev.h>
#include <string.h>

int zillot::chardev::print(int32_t arg) 
{ 
	char buf[32];
	char* eptr = i32toa(arg, buf, 10);
	return write(buf, eptr - buf); 
}

int zillot::chardev::print(const char * arg) 
{
	return write(arg, strlen(arg));
}