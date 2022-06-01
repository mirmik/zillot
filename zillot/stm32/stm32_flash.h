#ifndef ZILLOT_STM32_FLASH_H
#define ZILLOT_STM32_FLASH_H

#include <stdint.h>
#include <sys/cdefs.h>

#ifndef FLASH_VOLTAGE_RANGE_1
#define FLASH_VOLTAGE_RANGE_1 0x00
#endif

#ifndef FLASH_VOLTAGE_RANGE_2
#define FLASH_VOLTAGE_RANGE_2 0x01
#endif

#ifndef FLASH_VOLTAGE_RANGE_3
#define FLASH_VOLTAGE_RANGE_3 0x02
#endif

#ifndef FLASH_VOLTAGE_RANGE_4
#define FLASH_VOLTAGE_RANGE_4 0x03
#endif

__BEGIN_DECLS

void stm32_flash_unlock();
void stm32_flash_lock();

void stm32_flash_write_word(uint32_t address, uint32_t data);
uint32_t stm32_flash_read_word(uint32_t address);
void stm32_flash_erase_sector(uint32_t sector, uint8_t voltage_code);
void stm32_flash_write_finish();

__END_DECLS

#endif