#ifndef GENOS_AVR_STARTUP_H
#define GENOS_AVR_STARTUP_H

#include <avr/io.h>

#define STACKBASE (RAMEND)
#define RESET_STACK() SP = STACKBASE
#define SET_STACK_POINTER(arg) SP = arg

#if defined(__AVR_ATmega2560__)
#	define HAVE_RAMPZ
#	define HAVE_EIND
#elif defined(__AVR_ATmega328P__) || defined (__AVR_ATmega328__)  || defined (__AVR_ATmega168__)
#else 
#	error "unrecognized chip"
#endif

#endif