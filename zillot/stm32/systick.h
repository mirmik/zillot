#ifndef ZILLOT_SYSTICK_H
#define ZILLOT_SYSTICK_H

namespace zillot 
{
	class systick 
	{
	public:
		void systick_config(uint32_t ticks);
		uint32_t read_reload_register();
	}
}

#endif