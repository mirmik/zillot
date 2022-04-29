import licant

licant.module("zillot.arm",
	srcdir="arm/internal/asm",
	include_paths = ["arm/internal"],
	sources = ["context.c", "switch_context.S", "delay.c", "hardfault.c"],
)

licant.module("zillot.armv7e-m",
	sources = [],
	include_paths = ["armv7e-m/internal"],
	mdepends = [
		"zillot.arm"
	]
)

licant.module("zillot.cortex-m4",
	mdepends = ["zillot.armv7e-m"],
	include_paths=["cortex-m4"]
)

licant.module("zillot.cortex-m7",
	mdepends = ["zillot.armv7e-m"],
	include_paths=["cortex-m7"]
)

