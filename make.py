#!/usr/bin/env python3

import licant

licant.include("igris")
licant.execute_recursive("zillot", ".g.py")

licant.cxx_application("avr_test_build", 
	toolchain = licant.gcc_toolchain("avr-"),

	sources=["zillot/main_stub.c"],
	
	mdepends = [
		"zillot.chip.avr.atmega2560",
		"zillot.drivers.avr",
		"igris.include",
		"igris.util",
		"igris.semaphore",
		("igris.syslock", "irqs"),
		("igris.dprint", "stub"),
	],
	
	include_paths = [
		"arch/avr",
		"."
	],

	cxx_flags = "-flto -ffunction-sections -fdata-sections -Wl,--gc-sections -Os -Werror=all -Werror=extra -fno-rtti -fno-exceptions",
	cc_flags = "-flto -ffunction-sections -fdata-sections -Wl,--gc-sections -Os -Werror=all -Werror=extra -fno-exceptions",
	ld_flags = "-flto -ffunction-sections -fdata-sections -Wl,--gc-sections -Os -Wall -Wextra -fno-rtti -fno-exceptions",

	defines = ["F_CPU=16000000"]
)

licant.ex("avr_test_build")
