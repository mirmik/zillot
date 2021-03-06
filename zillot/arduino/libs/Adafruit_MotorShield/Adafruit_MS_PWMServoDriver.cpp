/*************************************************** 
	This is a library for our Adafruit 16-channel PWM & Servo driver

	Pick one up today in the adafruit shop!
	------> http://www.adafruit.com/products/815

	These displays use I2C to communicate, 2 pins are required to  
	interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	Written by Limor Fried/Ladyada for Adafruit Industries.  
	BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MS_PWMServoDriver.h"
#include <math.h>

#include <genos/schedee_api.h>

Adafruit_MS_PWMServoDriver::Adafruit_MS_PWMServoDriver(uint8_t addr) {
	_i2caddr = addr;
}

void Adafruit_MS_PWMServoDriver::begin(i2c_bus_device* i2c) {
	this->i2c = i2c;
	reset();
}

void Adafruit_MS_PWMServoDriver::reset(void) {
	write8(PCA9685_MODE1, 0x0);
}

void Adafruit_MS_PWMServoDriver::setPWMFreq(float freq) {
	//Serial.print("Attempting to set freq ");
	//Serial.println(freq);
	
	freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).

	float prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	//Serial.print("Estimated pre-scale: "); Serial.println(prescaleval);
	uint8_t prescale = floor(prescaleval + 0.5);
	//Serial.print("Final pre-scale: "); Serial.println(prescale);  
	
	uint8_t oldmode = read8(PCA9685_MODE1);
	//dprln("oldmode:", oldmode);

	uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
	write8(PCA9685_MODE1, newmode); // go to sleep
	write8(PCA9685_PRESCALE, prescale); // set the prescaler
	write8(PCA9685_MODE1, oldmode);
	genos::current_schedee_msleep(5);
	write8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
																					// This is why the beginTransmission below was not working.
	//  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);*/
}

void Adafruit_MS_PWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
	//Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);
	//dprln("Setting PWM", num, ":", on, ",", off);

	char outdata[5];
	outdata[0] = LED0_ON_L+4*num;
	outdata[1] = on;
	outdata[2] = on>>8;
	outdata[3] = off;
	outdata[4] = off>>8;

	i2c->ops->write(i2c, _i2caddr, outdata, 5);
}

uint8_t Adafruit_MS_PWMServoDriver::read8(uint8_t addr) {
	char indata[1];
	char outdata[1];
	outdata[0] = addr;
	i2c_writeread(i2c, _i2caddr, outdata, 1, indata, 1);
	return indata[0];


/*  WIRE.beginTransmission(_i2caddr);
#if ARDUINO >= 100
	WIRE.write(addr);
#else
	WIRE.send(addr);
#endif
	WIRE.endTransmission();

	WIRE.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
#if ARDUINO >= 100
	return WIRE.read();
#else
	return WIRE.receive();
#endif*/
}

void Adafruit_MS_PWMServoDriver::write8(uint8_t addr, uint8_t d) {
	char outdata[2];
	outdata[0] = addr;
	outdata[1] = d;
	i2c->ops->write(i2c, _i2caddr, outdata, 2);
	


/*  WIRE.beginTransmission(_i2caddr);
#if ARDUINO >= 100
	WIRE.write(addr);
	WIRE.write(d);
#else
	WIRE.send(addr);
	WIRE.send(d);
#endif
	WIRE.endTransmission();*/
}
