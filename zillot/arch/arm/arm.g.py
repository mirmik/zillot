import licant

licant.module("hal.arm",
	srcdir="src",
	include_paths = ["src"],
	sources = ["context.c", "switch_context.S", "delay.c", "hardfault.c"],
)

licant.module("hal.arm.armv7e-m",
	sources = ["armv7e-m/src/nvic.c"],
	include_paths = ["src"],
	mdepends = [
		"hal.arm"
	]
)

licant.module("cpu.arm.cortex-m4",
	mdepends=["hal.arm", "arch.cortex-m4"]	
)

licant.module("arch.cortex-m4",
	mdepends = ["hal.arm.armv7e-m"],
	include_paths=["cortex-m4/include"]
)

licant.module("arch.cortex-m7",
	mdepends = ["hal.arm.armv7e-m"],
	include_paths=["cortex-m7"]
)

