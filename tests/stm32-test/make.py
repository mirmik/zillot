#!/usr/bin/env python3

import licant

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
                           ("igris.syslock", "irqs"),
                           ("igris.systime", "jiffies"),
                           "zillot.stm32f407vg",
                           "newlib-stub"
                       ],
                       cxx_flags="-fmax-errors=1 -mthumb -mcpu=cortex-m4 -fno-exceptions -fno-rtti -fno-threadsafe-statics -mfloat-abi=hard -mfpu=fpv4-sp-d16  -D__FPU_USED=1",
                       cc_flags="-fmax-errors=1 -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16  -D__FPU_USED=1",
                       ld_flags=" -Wl,--gc-sections -fmax-errors=1 -mthumb -mcpu=cortex-m4 -fno-exceptions -fno-rtti  -mfloat-abi=hard -mfpu=fpv4-sp-d16  -D__FPU_USED=1",
                       )

if __name__ == "__main__":
    licant.ex("stm32-firmware.elf")
