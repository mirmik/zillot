#!/usr/bin/env python3
import licant
import os

licant.include("zillot")
licant.include("igris")

licant.cxx_application("firmware.elf",
	toolchain = licant.gcc_toolchain("avr-"),
	sources = ["main.cpp"],
	include_paths=["/usr/lib/avr/include/"],
	mdepends = [
		"igris.libc",
		"igris.std",
		"igris.posix",
		"igris.include",
		"igris.util",
		("igris.systime", "jiffies"),
		("igris.syslock", "irqs"),
		("igris.dprint", "diag"),
		"zillot.include",
		"zillot.avr.atmega2560",
		"zillot.arduino.mega",
	],

	cxx_flags = "-ffunction-sections -fdata-sections",
	cc_flags = "-ffunction-sections -fdata-sections",
	ld_flags = "-nostdinc -Wl,--gc-sections",
	libs=["gcc"],
	defines=["WITHOUT_ATOF64"]
)

default_file = "/dev/ttyACM0"

@licant.routine(deps=["firmware.elf"])
def install(src="firmware.hex", tgt=default_file, *args):
	for cmd in [
		"avr-objcopy -O ihex -R .eeprom -R .fuse firmware.elf firmware.hex",
		f"avrdude -P{tgt} -v -cwiring -patmega2560 -b115200 -D -Uflash:w:./{src} -u"
	]:
		print(cmd)
		os.system(cmd)

@licant.routine
def terminal(path=default_file):
	os.system("sudo gtkterm -p {} -s 115200 --parity none".format(path))

licant.ex("firmware.elf")