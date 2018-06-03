#pragma once
#include <Arduino.h>
#include "config.h"

/*
in function INTERPRET -> setup for given command
in function EXECUTE -> loop of the commnad

COMMANDS INTERPRETED HERE:

G00		rapid positioning		TODO
G01		linear interpolation	TODO
G02		Clockwise circ. interp	TODO
G03		CClocwise circ. interp	TODO
G04		DWELL (DELAY)			TODO
G28		RETURN HOME				TODO

M03		SPINDLE CLOCKWISE		TODO
M04		SPINDLE CCLOCKWISE		TODO
M05		SPINDLE STOP			TODO

U00		ROTATE TABLE			TODO
U01		board locking command	TODO
U02		board unlock command	TODO
U03		LEVELING				TODO

COMMANDS NOT INTERPRETED HERE:

U04		COMMUNICATION TEST		TODO
U05		Standard reply			TODO
U06		ERROR command			TODO
U07		begin process			TODO
U08		end process				TODO
U09		reset					TODO
 */
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
	float _U;
	float _LV[20]; // LocalVariables vector 

	bool UnitIsCm;

	uint32_t _numberOfStepsRequired;
	uint32_t _currentStep;

	float _XPosition;
	float _YPosition;
	float _ZPosition;
	float _RotPosition;
	float _TablePosition;

	uint8_t _TableSpeed;
	uint8_t _TableRotationSpeed;
	uint8_t _SpindleSpeed;
	uint16_t _CartesianSpeed;

	void SetSteppersEn(bool);

	void G00_SetUp();
	void G01_SetUp();
	void G28_SetUp();

	void G00_Execute();
	void G01_Execute();
	void G28_Execute();


public:
	GCodeInterpreter();
	~GCodeInterpreter();

	void PrepareForExecution();
	void ExecuteStep();
	bool Interpret(String);
	void Clear();
	void ExecutionIsComplete();


};


extern GCodeInterpreter Command;

