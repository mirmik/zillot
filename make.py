#!/usr/bin/env python3

import licant

licant.include("igris")
licant.execute_recursive("arch", ".g.py")

licant.cxx_application("avr_test_build", 
	toolchain = licant.gcc_toolchain("avr-"),

	sources=["zillot/main_stub.c"],
	
	mdepends = [
		"zillot.chip.avr-atmega2560",
		"zillot.avr-common",
		"igris.include",
		"igris.util",
		("igris.dprint", "stub"),
	],
	
	include_paths = [
		"arch/avr",
		"."
	]
)

licant.ex("avr_test_build")