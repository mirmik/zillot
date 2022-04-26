import licant

licant.module("zillot.arm",
	srcdir="src",
	include_paths = ["src"],
	sources = ["context.c", "switch_context.S", "delay.c", "hardfault.c"],
)

licant.module("zillot.armv7e-m",
	sources = [
		"armv7e-m/src/nvic.c"
	],
	include_paths = ["armv7e-m/src"],
	mdepends = [
		"zillot.arm"
	]
)

licant.module("zillot.cortex-m4",
	mdepends=["zillot.arm", "zillot.cortex-m4"]	
)

licant.module("zillot.cortex-m4",
	mdepends = ["zillot.armv7e-m"],
	include_paths=["cortex-m4/include"]
)

licant.module("zillot.cortex-m7",
	mdepends = ["zillot.armv7e-m"],
	include_paths=["cortex-m7"]
)

