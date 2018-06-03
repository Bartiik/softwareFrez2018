#pragma once
#include <Arduino.h>
#include "config.h"

/*
in function INTERPRET -> setup for given command
in function EXECUTE -> loop of the commnad

COMMANDS INTERPRETED HERE:

G00		rapid positioning		
G01		linear interpolation	
G02		Clockwise circ. interp	TODO
G03		CClocwise circ. interp	TODO
G04		DWELL (DELAY)			
G28		RETURN HOME				WIP

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
	float _P;
	float _LV[20]; // LocalVariables vector 

	bool _spindleIsWorking;

	uint32_t _numberOfStepsRequired;
	uint32_t _currentStep;

	float _XPosition;
	float _YPosition;
	float _ZPosition;
	float _RotPosition;
	float _TablePosition;

	uint16_t _TableSpeed;
	uint16_t _TableRotationSpeed;
	uint16_t _SpindleSpeed;
	uint16_t _CartesianSpeed;

	void SetSteppersEn(bool);

	void G00_SetUp();
	void G01_SetUp();
	void G28_SetUp();
	void G04_SetUp();

	void M03_SetUp();
	void M05_SetUp();
	
	void G00_Execute();
	void G01_Execute();
	void G04_Execute();
	void M03_Execute();
	void M05_Execute();
	void SpindleAccelerate();
	void SpindleDecelerate();
	void S_SetUp();
public:
	void G28_Execute();

	uint32_t time;


	GCodeInterpreter();
	~GCodeInterpreter();

	void PrepareForExecution();
	void ExecuteStep();
	bool Interpret(String);
	void Clear();
	void ExecutionIsComplete();


};


extern GCodeInterpreter Command;

