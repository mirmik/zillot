import licant

licant.module("zillot.avr-common",
	sources= [
		"asm/avr_gpio.c",
		"asm/avr_usart.c",
		"asm/avr_timer.c",
		"asm/avr_arch.c",
		"asm/avr_diag.c",
		"asm/avr_systime.c",
	],
	include_paths = ["."]
)

licant.module("zillot.chip.avr.atmega2560",
	mdepends=["zillot.avr-common"],
	cxx_flags="-mmcu=atmega2560",
	cc_flags="-mmcu=atmega2560",
	ld_flags="-mmcu=atmega2560"
)

licant.module("zillot.chip.avr.atmega328p",
	mdepends=["zillot.avr-common"],
	cxx_flags="-mmcu=atmega328p",
	cc_flags="-mmcu=atmega328p",
	ld_flags="-mmcu=atmega328p"
)