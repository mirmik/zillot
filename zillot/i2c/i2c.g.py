import licant

licant.module("zillot.i2c-common",
	sources=["i2c_device.c"]
)

licant.module("zillot.avr_i2c_device",
	sources = ["avr_i2c_device.c"],
	mdepends = ["zillot.i2c-common"]
)