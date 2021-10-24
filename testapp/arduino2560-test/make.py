#!/usr/bin/env python3
import licant
import os

licant.include("zillot")
licant.include("igris")

licant.cxx_application("firmware",
	toolchain = licant.gcc_toolchain("avr-"),
	sources = ["main.cpp"],
	mdepends = [
		"igris.include",
		"igris.util",
		("igris.dprint", "stub"),

		"zillot.include",
		"zillot.chip.avr.atmega2560",
		"zillot.arduino.mega"
	],

	cxx_flags = "-ffunction-sections -fdata-sections",
	cc_flags = "-ffunction-sections -fdata-sections",
	ld_flags = "-Wl,--gc-sections"
)

default_file = "/dev/ttyACM0"

@licant.routine(deps=["firmware"])
def install(src="firmware.hex", tgt=default_file, *args):
	for cmd in [
		"avr-objcopy -O ihex -R .eeprom -R .fuse firmware firmware.hex",
		f"avrdude -P{tgt} -v -cwiring -patmega2560 -b115200 -D -Uflash:w:./{src} -u"
	]:
		print(cmd)
		os.system(cmd)

@licant.routine
def terminal(path=default_file):
	os.system("sudo gtkterm -p {} -s 115200 --parity none".format(path))

licant.ex("firmware")