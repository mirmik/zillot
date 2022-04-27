#!/usr/bin/env python3

import licant

licant.execute_recursive("zillot", ".g.py")

licant.module("zillot.diag", "stub", 
	sources = ["zillot/diag_stub.c"]
)

licant.module("zillot.diag", "impl", 
	sources = ["zillot/diag_impl.c"], 
	default=True
)

licant.module("igris.dprint", "diag", 
	mdepends=[
		"zillot.diag",
		"igris.dprint.common"
	],
	sources = ["zillot/dprint_diag.c"]
)

licant.module("zillot.include",
	include_paths = ["."]
)

licant.module("zillot.arduino.avr.systime",
	sources=["zillot/arduino/avr-systick.c"]
)

licant.module("zillot",
	mdepends=[
		"zillot.include",
		"igris.semaphore"
	]
)

licant.module("zillot.armv7e-m", 
	include_paths=[ "zillot/armv7e-m/internal" ]
)

licant.module("zillot.cortex-m4", 
	include_paths=[ "zillot/cortex-m4" ],
	mdepends = [ "zillot.armv7e-m" ]
)

licant.module("zillot.stm32",
	include_paths=[ "zillot/stm32/internal" ],
	mdepends=[
		"zillot.include",
	]	
)