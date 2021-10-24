import licant

licant.module("zillot.arduino-compat", 
	include_paths=["."], 
	defines=["ARDUINO=100"])

licant.module("zillot.arduino.mega",
	mdepends = ["zillot.arduino-compat"],
	defines = ["BOARD_ARDUINO_MEGA=1"]
)