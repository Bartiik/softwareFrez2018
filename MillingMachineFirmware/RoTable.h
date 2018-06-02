#pragma once
#include "config.h"
#include "SMotor.h"
class RoTable
{
public:
	RoTable();
	~RoTable();
	void init();
	void setRotationSpeed(int16_t);
	void rotationSleep(bool);
	SMotor holder;
};

extern RoTable Table;