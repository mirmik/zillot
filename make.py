#!/usr/bin/env python3
import licant

licant.execute("./tests/arduino2560-test/make.py")
licant.execute("./tests/stm32-test/make.py")
licant.execute("./tests/common/make.py")

licant.fileset("all", ["runtests", "arduino2560-firmware.elf", "stm32-firmware.elf"])

licant.ex("all")
