#!/usr/bin/env python3

import licant

licant.include("igris")
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