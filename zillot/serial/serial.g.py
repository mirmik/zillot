import licant

licant.module("zillot.drivers.serial.common",
	sources=[]
)

licant.module("zillot.drivers.serial.avr",
	sources=[
		"avr_usart_device.c"
	],
	mdepends=[
		"zillot.drivers.serial.common"
	]
)