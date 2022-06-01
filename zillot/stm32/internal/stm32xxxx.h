#ifndef STM32XXXX_H
#define STM32XXXX_H

#define STM32F4XX 1
#define STM32F4xx 1
#define STM32F446 1

#ifdef STM32G4XX
#include "stm32g4xx.h"
#elif defined(STM32F4XX)
#include "stm32f4xx.h"
#elif defined(STM32L4XX)
#include "stm32l4xx.h"
#elif defined(STM32F7XX)
#include "stm32f7xx.h"
#else 
#error "undefined arch"
#endif

#endif