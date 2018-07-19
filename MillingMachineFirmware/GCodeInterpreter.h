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
G20		IN units				L 
G21		MM units				L 
G28		RETURN HOME				H
G29		AUTOMATIC bed leveling	H TODO
G30		single Z probe			M 
G90		Absolute positioning	L TODO bool changes, but G00 and G00 need change
G91		relative positioning	L TODO bool changes, but G00 and G00 need change
G92		set position			L


M03		SPINDLE CLOCKWISE		L
M04		SPINDLE CCLOCKWISE		L
M05		SPINDLE STOP			L
M48		Probe test				H
M92		steps per mm			L 
M500	save settings			H 
M501	restore settings		H 

U00		ROTATE TABLE			H
U01		board locking command	L
U02		board unlock command	L
U10		ROTATE TABLE			H TODO
U11		SET begin point			L 
U12		GOTO begin point		H 

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

	int64_t _XinSTEPS;
	int64_t _YinSTEPS;
	int64_t _ZinSTEPS;

	int32_t _ZProbeValue;

	uint16_t _TableSpeed;
	uint16_t _TableRotationSpeed;
	uint16_t _SpindleSpeed;
	uint16_t _CartesianSpeed;

	bool _SensorIsWorking;
	
	uint16_t _StepsPerMMX;
	uint16_t _StepsPerMMY;
	uint16_t _StepsPerMMZ;

	uint16_t _BEGINX;
	uint16_t _BEGINY;

	bool CheckMovementPossibility(float*, float*, float*);
	void RapidMotion_SetUp(float*, float*, float*, int32_t, int32_t, int32_t);
	void LinearMotion_SetUp(float*, float*, float*, float*, float*, float*, float*, float*, float*, int32_t, int32_t, int32_t);
	void G02_SetUp();
	void G03_SetUp();
	void Dwell_SetUp();
	void GotoBase_SetUp(float*);
	void G29_SetUp(float*, float*, float*, float*, float*, float*, float*, float*, float*, float*);
	void SpindleStart_SetUp(float*);
	void SpindleStop_SetUp(float*);
	void SensorCheck_SetUp(float*, float*);
	void setPosition_SetUp(float, float, float);
	void setPosition_SetUp(char, float);
	void setStepsPerMM_SetUp();
	void saveToEEPROM_SetUp();
	void readFromEEPROM_SetUp();
	void rotateTable_SetUp();
	void BoardLock_SetUp();
	void U12_SetUp(float*, float*, float*);

	
	bool RapidMotion_Execute(float*, float*, float*, int32_t, int32_t, int32_t);
	bool LinearMotion_Execute(float*, float*, float*, float*, float*, float*, float*, float*, float*, int32_t, int32_t, int32_t);
	bool G02_Execute();
	bool G03_Execute();
	bool Dwell_Execute();
	bool GotoBase_Execute(float*);
	bool G29_Execute(float*, float*, float*, float*, float*, float*, float*, float*, float*, float*);
	bool ZProbe_Execute();
	bool SpindleStart_Execute(float*);
	bool SpindleStop_Execute(float*);
	bool SensorCheck_Execute(float*, float*, float*, float*, float*);
	bool rotateTable_Execute();
	bool boardLock_Execute();
	bool boardUnlock_Execute();
	bool U12_Execute(float*, float*, float*);

	void CalculateSteps();

	uint16_t arraySizeX;
	uint16_t arraySizeY;
	uint16_t PCBsizeX;
	uint16_t PCBsizeY;

	int16_t* LevelArray;

	int16_t calculateLevel(int16_t, int16_t);

public:

	uint32_t time;

	void SetSteppersEn(bool);

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

