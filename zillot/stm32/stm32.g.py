import licant

licant.module("zillot.stm32.common",
	include_paths=["internal"],
	sources=[
		"usart.cpp",

		"stm32_usart.c",
		"stm32_pll.c",
		"stm32_timer.c",
		"stm32_clockbus.c",
		"stm32_systick.c",
		"stm32_rcc.c",
		"stm32_gpio.c",
		"stm32_diag.c",
		"stm32_watchdog.c",
	],
	mdepends = [
		"zillot.include",
		#"cpu.stm32.irqtable", 
	]
)

licant.module("zillot.stm32.irqtable",
	sources=[
		"src/stm32_vectors.S",
	],
	ldscripts=["ldscripts/stm32_common_alt.ld"],
)

licant.module("zillot.stm32f4",
	defines = ["STM32F4XX", "STM32F4xx"],
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

licant.module("zillot.stm32.spl",
	sources=[
		"internal/spl/stm32f4xx_tim.c",
		"internal/spl/stm32f4xx_rcc.c",
	]
)

licant.module("zillot.stm32.vectors",
	sources=[
		"stm32_vectors.S",
		"stm32_start.c"
	]
)