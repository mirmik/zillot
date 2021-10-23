#!/usr/bin/env python3

import licant

licant.include("igris")
licant.execute_recursive("zillot", ".g.py")

licant.module("zillot.drivers.avr",
	sources = ["zillot/serial/avr_usart.c"]
)

licant.cxx_application("avr_test_build", 
	toolchain = licant.gcc_toolchain("avr-"),

	sources=["zillot/main_stub.c"],
	
	mdepends = [
		"zillot.chip.avr-atmega2560",
		"zillot.avr-common",
		"zillot.drivers.avr",
		"igris.include",
		"igris.util",
		("igris.dprint", "stub"),
	],
	
	include_paths = [
		"arch/avr",
		"."
	],

	defines = ["F_CPU=16000000"]
)

licant.ex("avr_test_build")