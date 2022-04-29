#ifndef ZILLOT_COMMON_ABSTRACT_PIN_H
#define ZILLOT_COMMON_ABSTRACT_PIN_H

namespace zillot 
{
	class abstract_pin 
	{
		public:
			virtual void write(int val) = 0;
			virtual int read() = 0;
			virtual void toggle() = 0;
			virtual void pull_up(int lvl) = 0;
			virtual int setup(uint32_t mode) = 0;

			void set(int val) { write(val); }
			int get() { return read(); }	
	};
}

#endif