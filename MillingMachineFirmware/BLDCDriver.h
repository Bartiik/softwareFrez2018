#pragma once

#include <Servo.h>
#include "config.h"
class BLDCDriver
{
private:
	Servo _bldc;
public:
	BLDCDriver();
	~BLDCDriver();
	void init();
	void setSpeed(uint16_t);

};

extern BLDCDriver spindle;