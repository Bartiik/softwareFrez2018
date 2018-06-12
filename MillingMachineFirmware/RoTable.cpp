#include "RoTable.h"
#include "Communication.h"

RoTable Table;

RoTable::RoTable()
{
	_tablePosition = 0;
}


RoTable::~RoTable()
{

}

void RoTable::setTablePosition(bool TP) {
	_tablePosition = TP;
}

bool RoTable::returnTablePosition() {
	return _tablePosition;
}

void RoTable::init()
{
	holder.Init(TABLE_DIR_PIN, TABLE_STEP_PIN, TABLE_ENABLE_PIN);
	pinMode(DC_DIR_2, OUTPUT);
	pinMode(DC_ENABLE, OUTPUT);
	pinMode(DC_DIR_1, OUTPUT);
	analogWrite(DC_ENABLE, BLDC_DEFAULT_SPEED);
	Table.stop();
}

void RoTable::setRotationSpeed(int16_t speed)
{
	bool dir;
	uint8_t val;
	if (speed < DC_MINIMUM_SPEED_VALUE)
	{
		val = DC_MAXIMUM_SPEED_VALUE;
		dir = COUNTER_CLOCKWISE;
	}
	else if (speed < 0)
	{
		val = -speed;
		dir = COUNTER_CLOCKWISE;
	}
	else if (speed < 255)
	{
		val = speed;
		dir = CLOCKWISE;
	}
	else
	{
		val = DC_MAXIMUM_SPEED_VALUE;
		dir = CLOCKWISE;
	}
	if (val == 0)
	{
		digitalWrite(DC_DIR_2, dir);
		digitalWrite(DC_DIR_1, dir);
	}
	else
	{
		digitalWrite(DC_DIR_2, dir);
		digitalWrite(DC_DIR_1, !dir);
	}

	analogWrite(DC_ENABLE, val);



}



void RoTable::rotateClockwise()
{
	analogWrite(DC_ENABLE, ROTATION_TABLE_SPEED);
	digitalWrite(DC_DIR_2, HIGH);
	digitalWrite(DC_DIR_1, LOW);
}
void RoTable::rotateCounterClockwise()
{
	analogWrite(DC_ENABLE, ROTATION_TABLE_SPEED);
	digitalWrite(DC_DIR_2, LOW);
	digitalWrite(DC_DIR_1, HIGH);
}
void RoTable::stop()
{
	analogWrite(DC_ENABLE, BLDC_MAXIMUM_SPEED_VALUE);
	digitalWrite(DC_DIR_2, HIGH);
	digitalWrite(DC_DIR_1, HIGH);
}