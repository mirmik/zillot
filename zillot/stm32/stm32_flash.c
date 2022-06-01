#include <stm32xxxx.h>
#include <zillot/stm32/stm32_flash.h>

#ifndef FLASH_KEY1
#define FLASH_KEY1 0x45670123
#endif

#ifndef FLASH_KEY2  
#define FLASH_KEY2 0xCDEF89AB
#endif

#define FLASH_CR_VOS_Pos 28
#define FLASH_CR_VOS_Msk (0x3u << FLASH_CR_VOS_Pos)
#define FLASH_CR_SNB_Pos 3
#define FLASH_CR_SNB_Msk (0x1fu << FLASH_CR_SNB_Pos)
#define FLASH_CR_PSIZE_Pos 8
#define FLASH_CR_PSIZE_Msk (0x3u << FLASH_CR_PSIZE_Pos)

#define FLASH_PSIZE_BYTE (0x00u << FLASH_CR_PSIZE_Pos)
#define FLASH_PSIZE_HALF_WORD (0x01u << FLASH_CR_PSIZE_Pos)
#define FLASH_PSIZE_WORD (0x02u << FLASH_CR_PSIZE_Pos)
#define FLASH_PSIZE_DOUBLE_WORD (0x03u << FLASH_CR_PSIZE_Pos)


void stm32_flash_unlock() {
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
    while (FLASH->SR & FLASH_SR_BSY);
}

void stm32_flash_lock() {
    while (FLASH->SR & FLASH_SR_BSY);
    FLASH->CR |= FLASH_CR_LOCK;
}

void stm32_flash_write_word(uint32_t address, uint32_t data) 
{    
    FLASH->CR &= ~FLASH_CR_PSIZE;
    FLASH->CR |= FLASH_PSIZE_WORD;

    FLASH->CR |= FLASH_CR_PG;
    *(__IO uint32_t*)address = data;
    while (FLASH->SR & FLASH_SR_BSY);
    FLASH->CR &= ~FLASH_CR_PG;
}

uint32_t stm32_flash_read_word(uint32_t address) 
{
    return *(__IO uint32_t*)address;
}

void stm32_flash_erase_sector(uint32_t sector, uint8_t voltage_code) 
{
    uint32_t tmp_psize = 0U;

  if (voltage_code == FLASH_VOLTAGE_RANGE_1)
  {
    tmp_psize = FLASH_PSIZE_BYTE;
  }
  else if (voltage_code == FLASH_VOLTAGE_RANGE_2)
  {
    tmp_psize = FLASH_PSIZE_HALF_WORD;
  }
  else if (voltage_code == FLASH_VOLTAGE_RANGE_3)
  {
    tmp_psize = FLASH_PSIZE_WORD;
  }
  else
  {
    tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
  }

  /* If the previous operation is completed, proceed to erase the sector */
  FLASH->CR &= ~FLASH_CR_PSIZE;
  FLASH->CR |= tmp_psize;
  FLASH->CR &= ~ FLASH_CR_SNB;
  FLASH->CR |= FLASH_CR_SER | (sector << FLASH_CR_SNB_Pos);
  FLASH->CR |= FLASH_CR_STRT;
}

void stm32_flash_write_finish() 
{
    FLASH->CR &= ~FLASH_CR_PG;
}
