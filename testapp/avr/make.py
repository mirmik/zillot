#!/usr/bin/env python3
import licant

licant.include("zillot")
licant.include("igris")


licant.cxx_application("firmware",
	toolchain = licant.gcc_toolchain("avr-"),
	sources = ["main.cpp"],
	mdepends = [
		"igris.include",
		"zillot.chip.avr.atmega2560"
	]
)

licant.ex("firmware")