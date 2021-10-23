#!/usr/bin/env python3

import licant

licant.include("igris")
licant.execute_recursive("zillot", ".g.py")

licant.module("zillot.include",
	include_paths = ["."]
)