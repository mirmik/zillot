#!/usr/bin/env python3

import licant
import os

licant.include("igris")
licant.include("zillot", "../../zillot.g.py")

licant.cxx_application("stm32-firmware.elf",
                       builddir="stm32build",
                       toolchain=licant.gcc_toolchain("arm-none-eabi-"),
                       sources=["main.cpp"],
                       mdepends=[
                           "igris.include",
                           ("igris.dprint", "zillot.diag"),
                           "igris.util",
                           "igris.utilxx",
                           "zillot.stm32.irqtable",
                           "zillot.irqtable",
                           ("igris.syslock", "irqs"),
                           ("igris.systime", "jiffies"),
                           # "zillot.stm32f407vg",
                           "zillot.stm32f401re",
                           "newlib-stub",
                           "stm32.irqtable_ldscript.stm32f401re"
                       ],
                       cxx_flags="-g -ffunction-sections -fdata-sections -mthumb -mcpu=cortex-m4 -fno-exceptions -fno-rtti -fno-threadsafe-statics -mfloat-abi=hard -mfpu=fpv4-sp-d16  -D__FPU_USED=1",
                       cc_flags="-g -ffunction-sections -fdata-sections -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16  -D__FPU_USED=1",
                       ld_flags="-g -ffunction-sections -fdata-sections -Wl,--gc-sections -fmax-errors=1 -mthumb -mcpu=cortex-m4 -fno-exceptions -fno-rtti  -mfloat-abi=hard -mfpu=fpv4-sp-d16  -D__FPU_USED=1",
                       )


@licant.routine(deps=["stm32-firmware.elf"])
def flash():
    os.system("arm-none-eabi-objcopy -O binary stm32-firmware.elf stm32-firmware.bin")
    os.system("st-flash write stm32-firmware.bin 0x8000000")


if __name__ == "__main__":
    licant.ex("stm32-firmware.elf")
