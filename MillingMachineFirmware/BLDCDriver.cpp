#include "BLDCDriver.h"
#include "Communication.h"
BLDCDriver spindle;

BLDCDriver::BLDCDriver()
{
}


BLDCDriver::~BLDCDriver()
{
}

void BLDCDriver::init()
{
	_bldc.attach(SPINDLE_SIGNAL_PIN);
	setSpeed(0);
}
void BLDCDriver::setSpeed(uint16_t speed)
{
	
	uint16_t SpeedSignal;
	if (speed <= 1000)
	{
		SpeedSignal = BLDC_MINIMUM_SPEED_VALUE;
	}
	else if (speed < 2000)
	{
		SpeedSignal = speed;
	}
	else SpeedSignal = BLDC_MAXIMUM_SPEED_VALUE;
	
	MMcomm.SendMessage((String)SpeedSignal);
	_bldc.writeMicroseconds(SpeedSignal);
	
}