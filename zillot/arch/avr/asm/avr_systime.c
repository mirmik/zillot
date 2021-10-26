#include <avr/io.h>
#include <igris/time/jiffies-systime.h>

uint32_t systime_lomax() { return 256; }
uint32_t systime_lopart() { return TCNT0; }