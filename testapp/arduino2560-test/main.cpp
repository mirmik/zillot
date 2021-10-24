#include <asm/avr_gpio.h>
#include <Arduino.h>

int main() 
{
	pinMode(13, 1);
	digitalWrite(13, 1);

	while(1) {}
}