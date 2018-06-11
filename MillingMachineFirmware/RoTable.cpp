#include "RoTable.h"

RoTable Table;

RoTable::RoTable()
{

}


RoTable::~RoTable()
{

}

void RoTable::init()
{
	holder.Init(TABLE_DIR_PIN, TABLE_STEP_PIN, TABLE_ENABLE_PIN);
	pinMode(DC_PHASE, OUTPUT);
	pinMode(DC_ENABLE, OUTPUT);
	pinMode(DC_SLEEP, OUTPUT);
}

void RoTable::setRotationSpeed(int16_t speed)
{
	uint8_t val;
	bool dir;
	if (speed <= -DC_MINIMUM_SPEED_VALUE)
	{
		speed = DC_MAXIMUM_SPEED_VALUE;
		dir = COUNTER_CLOCKWISE;
	}
	else if (speed < 0)
	{
		speed = -speed;
		dir = COUNTER_CLOCKWISE;
	}
	else if (speed < 255)
	{
		dir = CLOCKWISE;
	}
	else
	{
		speed = DC_MAXIMUM_SPEED_VALUE;
		dir = CLOCKWISE;
	}

	digitalWrite(DC_PHASE, dir);
	analogWrite(DC_ENABLE, speed);
}

void RoTable::rotationSleep(bool setToWorking)
{
	digitalWrite(DC_SLEEP, setToWorking);
}