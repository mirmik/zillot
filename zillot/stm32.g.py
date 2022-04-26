import licant

licant.module("zillot.stm32.common",
	include_paths=["stm32/internal"],
	sources=[
		#"stm32_systick.c",
		#"stm32_usart.c",
		#"stm32_gpio.c",
		#"stm32_start.c",
		#"stm32_rcc.c",
		#"stm32_diag.c",
		#"stm32_arch.c",
		#"stm32_clockbus.c",
	],
	mdepends = [
		"zillot.include",
		#"cpu.stm32.irqtable", 
	],
	cxx_flags = "-mthumb -mcpu=cortex-m4 -fno-exceptions -fno-rtti -fno-threadsafe-statics -mfloat-abi=hard -mfpu=fpv4-sp-d16  -D__FPU_USED=1",
	cc_flags = "-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16  -D__FPU_USED=1",
	ld_flags = "-mthumb -mcpu=cortex-m4 -fno-exceptions -fno-rtti  -mfloat-abi=hard -mfpu=fpv4-sp-d16  -D__FPU_USED=1",
)

licant.module("zillot.stm32.irqtable",
	sources=[
		"src/stm32_vectors.S",
	],
	ldscripts=["ldscripts/stm32_common_alt.ld"],
)

licant.module("zillot.stm32f4",
	defines = ["STM32F4XX"],
	mdepends = 
	[
		"zillot.stm32.common", 
		"zillot.cortex-m4",
	],
	#sources = ["src/stm32f4/stm32f4_sysinit.c"]
)

licant.module("zillot.stm32g4",
	defines = ["STM32G4XX", "STM32G4xx"],
	mdepends = 
	[
		"zillot.stm32.common", 
		"zillot.cortex-m4",
	],
	#sources = [ "src/stm32g4/stm32g4_sysinit.c" ]
)

licant.module("zillot.stm32f401re",
	mdepends = ["zillot.stm32f4"],
	defines = ["CHIP_STM32F401", "STM32F401xE", "STM32F4XX"],
	ldscripts=["ldscripts/stm32f401re.ld"]
)

licant.module("zillot.stm32f407vg",
	mdepends = ["zillot.stm32f4"],
	defines = ["CHIP_STM32F407", "STM32F4XX", "STM32F407xx"],
	#ldscripts=["ldscripts/stm32f407vg.ld"]
)

licant.module("zillot.stm32g474re",
	defines = ["CHIP_STM32G474xx", "STM32G474xx"],
	mdepends = ["zillot.stm32g4"],
	ldscripts=["ldscripts/stm32g474re.ld"]
)

licant.module("zillot.stm32g431rb",
	defines = ["CHIP_STM32G431xx", "STM32G431xx"],
	mdepends = ["zillot.stm32g4"],
	ldscripts=["ldscripts/stm32g431rb.ld"]
)




















licant.module("arch.stm32_common.sources", 	
	sources= [
		"src/stm32_start.c",
		"src/stm32_vectors.S",
		"src/stm32_arch.c",
		"src/stm32_adc.c",
		"src/stm32_rcc.c",
		"src/stm32_gpio.c",
		"src/stm32_spi.c",
	#	"src/stm32_i2c.c",
		"src/stm32_usart.c",
		"src/stm32_diag.c",
		"src/stm32_systick.c",
		"src/stm32_clockbus.c",
		"src/stm32_watchdog.c",
		"src/stm32_pll.c",
	],
)

licant.module("arch.stm32_common.sources_l4", 	
	sources= [
		"src/stm32_start.c",
		"src/stm32_vectors.S",
		"src/stm32_arch.c",
	#	"src/stm32_adc.c",
		"src/stm32_rcc.c",
		"src/stm32_gpio.c",
		"src/stm32_spi.c",
		"src/stm32_usart.c",
		"src/stm32_diag.c",
		"src/stm32_systick.c",
		"src/stm32_clockbus.c",
		#"src/stm32_pll.c",
	],
)

licant.module("arch.stm32_common",
	include_paths = ["include", "st-device"],

	ldscripts= ["ldscripts/stm32_common.ld"],

	cc_flags = "-g -Wl,--gc-sections -nostdlib -nostdinc -fdata-sections -ffunction-sections -Wl,--gc-sections -flto -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__FPU_USED=1",
	cxx_flags = "-g -Wl,--gc-sections -nostdlib -nostdinc -fdata-sections -ffunction-sections -Wl,--gc-sections -flto -fno-rtti -fno-exceptions -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-threadsafe-statics  -D__FPU_USED=1 -ffunction-sections -fno-rtti -flto -fno-use-cxa-atexit",
	ld_flags = "-g -nostdlib -mthumb -mcpu=cortex-m4 -fno-rtti -fno-exceptions -fdata-sections -ffunction-sections -flto -Wl,--gc-sections -fno-use-cxa-atexit -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16",
	optimize= "-Os",

	libs = ["m", "gcc"]
)

licant.module("arch.stm32_usb",
	sources = ["src/stm32_usb.c"])

licant.module("arch.stm32g4",
	defines=["STM32G4XX", "CHIP_STM32G4XX"],
	sources=["src/stm32g4/stm32g4_sysinit.c"],
	mdepends = ["arch.cortex-m4", "arch.stm32_common", "arch.stm32_common.sources"]
)

licant.module("arch.stm32f4",
	defines=["STM32F4XX", "CHIP_STM32F4XX"],
	sources=["src/stm32f4/stm32f4_sysinit.c"],
	mdepends = ["arch.cortex-m4", "arch.stm32_common", "arch.stm32_common.sources"]
)

licant.module("arch.stm32l4",
	defines=["STM32L4XX", "CHIP_STM32L4XX"],
	sources=["src/stm32l4/stm32l4_sysinit.c"],
	mdepends = ["arch.cortex-m4", "arch.stm32_common", "arch.stm32_common.sources_l4"]
)

licant.module("arch.stm32f446re",
	defines=["STM32F446xx"],
	mdepends=["arch.stm32f4"],
	ldscripts=["ldscripts/stm32f446re.ld"]
)

licant.module("arch.stm32f401re", 
	defines = ["CHIP_STM32F401", "STM32F401xE"],
	mdepends = [ "arch.stm32f4" ],
	ldscripts = "ldscripts/stm32f401re.ld",
)

licant.module("arch.stm32f407vg", 
	defines = ["CHIP_STM32F407", "STM32F407xx"],
	mdepends = [
		"arch.stm32f4"
	],
	ldscripts = "ldscripts/stm32f407vg.ld",
)

licant.module("arch.stm32g431rb",
	defines=["STM32G431xx"],
	mdepends=["arch.stm32g4"],
	ldscripts=["ldscripts/stm32g431.ld"]
)

licant.module("arch.stm32g474re",
	defines=["STM32G474xx"],
	mdepends=["arch.stm32g4"],
	ldscripts=["ldscripts/stm32g474re.ld"]
)


licant.module("genos.hal", impl = "stm32l432", 
	defines = ["CHIP_STM32L432", "CHIP_STM32L432XX", "STM32L432xx"],
	mdepends=["arch.stm32l4", "arch.stm32_usb"],
	ldscripts = "ldscripts/stm32l432.ld",
)

licant.module("arch.stm32f746ng",
	defines=["STM32F746xx"],
	mdepends=["arch.stm32f7"],
	ldscripts=["ldscripts/stm32f746ng.ld"]
)











