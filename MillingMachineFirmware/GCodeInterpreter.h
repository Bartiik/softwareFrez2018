#pragma once
#include <Arduino.h>
#include "config.h"


class GCodeInterpreter
{
private:
	float _G;
	float _M;
	float _X;
	float _Y;
	float _Z;
	float _I;
	float _J;
	float _S;
	float _F;

	uint32_t _numberOfStepsRequired;
	uint32_t _currentStep;

	uint8_t *_XQueue;
	uint8_t *_YQueue;
	uint8_t *_ZQueue;
	uint8_t *_TableQueue;

	float _XPosition;
	float _YPosition;
	float _ZPosition;
	float _RotPosition;
	float _TablePosition;

	uint8_t _TableSpeed;
	uint8_t _TableRotationSpeed;
	uint8_t _SpindleSpeed;
	uint16_t _CartesianSpeed;

public:
	GCodeInterpreter();
	~GCodeInterpreter();
	void ExecuteStep();
	void Interpret(String);
	void Clear();


};


extern GCodeInterpreter Command;

