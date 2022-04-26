#!/usr/bin/env python3

import licant

licant.include("zillot", "../../zillot.g.py")

licant.cxx_application("firmware.elf",
	toolchain = licant.gcc_toolchain("arm-none-eabi-"),
	sources = [ "main.cpp" ],
	mdepends = [ "zillot.stm32f407vg" ]
)

licant.ex("firmware.elf")