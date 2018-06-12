#pragma once
#include "config.h"
#include "SMotor.h"
class RoTable
{
	bool _tablePosition;
public:
	RoTable();
	~RoTable();
	void setTablePosition(bool);
	bool returnTablePosition();
	void init();
	void setRotationSpeed(int16_t);
	SMotor holder;
	void rotateClockwise();
	void rotateCounterClockwise();
	void stop();
};

extern RoTable Table;