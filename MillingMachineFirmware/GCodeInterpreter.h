#pragma once
#include <Arduino.h>
#include "config.h"

/*
in function INTERPRET -> setup for given command
in function EXECUTE -> loop of the commnad

COMMANDS INTERPRETED HERE:

G00		rapid positioning		L
G01		linear interpolation	H
G02		Clockwise circ. interp	H TODO unnecessary
G03		CClocwise circ. interp	H TODO unnecessary
G04		DWELL (DELAY)			L
G20		MM units				L 
G21		IN units				L 
G28		RETURN HOME				H
G29		AUTOMATIC bed leveling	H TODO
G30		single Z probe			M TODO
G90		Absolute positioning	L TODO bool changes, but G00 and G00 need change
G91		relative positioning	L TODO bool changes, but G00 and G00 need change
G92		set position			L


M03		SPINDLE CLOCKWISE		L
M04		SPINDLE CCLOCKWISE		L
M05		SPINDLE STOP			L
M48		Probe test				H TODO
M92		steps per mm			L 
M500	save settings			H 
M501	restore settings		H 

U00		ROTATE TABLE			H
U01		board locking command	L
U02		board unlock command	L


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
	bool _unitsMM;
	bool _AbsoluteMotion;

	float _XPosition;
	float _YPosition;
	float _ZPosition;
	float _RotPosition;
	float _TablePosition;

	int16_t _XinSTEPS;
	int16_t _YinSTEPS;
	int16_t _ZinSTEPS;

	uint16_t _TableSpeed;
	uint16_t _TableRotationSpeed;
	uint16_t _SpindleSpeed;
	uint16_t _CartesianSpeed;

	
	uint16_t _StepsPerMMX;
	uint16_t _StepsPerMMY;
	uint16_t _StepsPerMMZ;

	void SetSteppersEn(bool);

	bool CheckMovementPossibility();
	void RapidMotion_SetUp(float*, float*, float*, int16_t, int16_t, int16_t);
	void LinearMotion_SetUp(float*, float*, float*, float*, float*, float*, float*, float*, float*, int16_t, int16_t, int16_t);
	void G02_SetUp();
	void G03_SetUp();
	void Dwell_SetUp();
	void GotoBase_SetUp(float*);
	void SpindleStart_SetUp(float*);
	void SpindleStop_SetUp(float*);
	void setPosition_SetUp(float, float, float);
	void setPosition_SetUp(char, float);
	void setStepsPerMM_SetUp();
	void saveToEEPROM_SetUp();
	void readFromEEPROM_SetUp();
	void rotateTable_SetUp();
	void BoardLock_SetUp();

	
	bool RapidMotion_Execute(float*, float*, float*, int16_t, int16_t, int16_t);
	bool LinearMotion_Execute(float*, float*, float*, float*, float*, float*, float*, float*, float*, int16_t, int16_t, int16_t);
	bool G02_Execute();
	bool G03_Execute();
	bool Dwell_Execute();
	bool GotoBase_Execute(float*);
	bool SpindleStart_Execute(float*);
	bool SpindleStop_Execute(float*);
	bool rotateTable_Execute();
	bool boardLock_Execute();
	bool boardUnlock_Execute();

	void CalculateSteps();


public:

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

