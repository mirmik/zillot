#!/usr/bin/env python3

import licant

licant.include("igris")
licant.include("zillot", "../../zillot.g.py")

licant.cxx_application("firmware.elf",
	toolchain = licant.gcc_toolchain("arm-none-eabi-"),
	sources = [ "main.cpp" ],
	mdepends = [
		"igris.include",
		"igris.dprint",
		"igris.util",
		"igris.utilxx",
		("igris.syslock", "irqs"),
		("igris.systime", "jiffies"),
		"zillot.stm32f407vg",
		"newlib-stub"
	],

	cxx_flags = "-ffunction-sections -fdata-sections",
	cc_flags = "-ffunction-sections -fdata-sections",
	ld_flags = "-nostdinc -Wl,--gc-sections",
)

licant.ex("firmware.elf")