#ifndef ZILLOT_STM32_CLOCKBUS_H
#define ZILLOT_STM32_CLOCKBUS_H

namespace zillot 
{
	class clockbus 
	{
	public:
		void set_hsi_mode();
		void set_hse_mode(); 
		void set_pll_mode();
	};
}

#endif