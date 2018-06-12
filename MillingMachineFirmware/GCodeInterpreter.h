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
G28		RETURN HOME				

M03		SPINDLE CLOCKWISE		
M04		SPINDLE CCLOCKWISE		
M05		SPINDLE STOP			

U00		ROTATE TABLE			TODO
U01		board locking command	TODO
U02		board unlock command	TODO
U03		LEVELING				TODO

COMMANDS NOT INTERPRETED HERE:

U04		COMMUNICATION TEST		
U05		Standard reply			
U06		ERROR command			
U07		begin process			
U08		end process				
U09		reset					
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
	void G02_SetUp();
	void G03_SetUp();
	void G28_SetUp();
	void G04_SetUp();
	void M03_SetUp();
	void M05_SetUp();
	void U00_SetUp();
	void U01_SetUp();
	
	void G00_Execute();
	void G01_Execute();
	void G02_Execute();
	void G03_Execute();
	void G04_Execute();
	void M03_Execute();
	void M05_Execute();
	void U00_Execute();
	void U01_Execute();
	void U02_Execute();
	void U03_Execute();

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
	String returnPosition();
	
};


extern GCodeInterpreter Command;

