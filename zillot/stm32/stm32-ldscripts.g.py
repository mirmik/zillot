import licant

licant.module("stm32.irqtable_ldscript.common",
              ldscripts=["ldscripts/stm32_common.ld"]
              )

licant.module("stm32.irqtable_ldscript.stm32f407vg",
              ldscripts=["ldscripts/stm32f407vg.ld"],
              mdepends=["stm32.irqtable_ldscript.common"]
              )

licant.module("stm32.irqtable_ldscript.stm32f401re",
              ldscripts=["ldscripts/stm32f401re.ld"],
              mdepends=["stm32.irqtable_ldscript.common"]
              )
