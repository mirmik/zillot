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
                           "igris.dprint",
                           "igris.util",
                           "igris.utilxx",
                           ("igris.syslock", "irqs"),
                           ("igris.systime", "jiffies"),
                           "zillot.stm32f407vg",
                           "newlib-stub"
                       ],

                       cxx_flags="-ffunction-sections -fdata-sections",
                       cc_flags="-ffunction-sections -fdata-sections",
                       ld_flags="-nostdinc -Wl,--gc-sections",
                       )

if __name__ == "__main__":
    licant.ex("stm32-firmware.elf")
