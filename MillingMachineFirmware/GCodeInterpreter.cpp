#include "GCodeInterpreter.h"
#include "Communication.h"
#include "MMStateMachine.h"
#include "SMotor.h"
#include "BLDCDriver.h"
#include "RoTable.h"
#include <EEPROM.h>
#include <math.h>
GCodeInterpreter Command;

GCodeInterpreter::GCodeInterpreter()
{
	setPosition_SetUp(0, 0, 0);
	_unitsMM = true;
	_SpindleSpeed = BLDC_DEFAULT_SPEED;
	_spindleIsWorking = false;
	readFromEEPROM_SetUp();
	arraySizeX = 11;
	arraySizeY = 11;
	//*LevelArray = (int16_t)realloc(LevelArray, sizeof(int16_t) * 121);
	/*for (int i = 0; i < 121; i++)
		LevelArray[i] = 0;*/
	Clear();
}

GCodeInterpreter::~GCodeInterpreter() 
{

}

/* autor: Bartek Kudroń
wyczyszczenie danych zawartych w klasie
*/
void GCodeInterpreter::Clear()
{
	_G = DUMMY_VALUE;
	_M = DUMMY_VALUE;
	_X = DUMMY_VALUE;
	_Y = DUMMY_VALUE;
	_Z = DUMMY_VALUE;
	_I = DUMMY_VALUE;
	_J = DUMMY_VALUE;
	_S = DUMMY_VALUE;
	_F = DUMMY_VALUE;
	_U = DUMMY_VALUE;
	for (int i = 0; i < sizeof(_LV) / sizeof(float); i++)
	{
		_LV[i] = DUMMY_VALUE;
	}

}

String GCodeInterpreter::returnPosition() 
{
	int32_t X = _XPosition / _StepsPerMMX * POSITION_ACCURACY_INVERSE;
	int32_t Y = _YPosition / _StepsPerMMY * POSITION_ACCURACY_INVERSE;
	int32_t Z = _ZPosition / _StepsPerMMZ * POSITION_ACCURACY_INVERSE;
	String position = "X" + String(X) + "Y" + String(Y) + "Z" + String(Z);
	return position;
}

void GCodeInterpreter::SetSteppersEn(bool EN) {
	XStepper.SetEnable(EN);
	YStepper.SetEnable(EN);
	ZStepper.SetEnable(EN);
}

/* autor: Maciej Wiecheć
preparing for execution G00
set dir for each axis
*/
void GCodeInterpreter::RapidMotion_SetUp(float *stepDirX, float *stepDirY, float *stepDirZ, int32_t wantedX, int32_t wantedY, int32_t wantedZ) {

	// dir in X-axis
	if (wantedX < _XPosition) 
	{
		*stepDirX = -1;
	}
	else if (wantedX > _XPosition) 
	{
		*stepDirX = 1;
	}
	else
	{
		*stepDirX = 0;
	}
	// dir in Y-axis
	if (wantedY < _YPosition) {
		*stepDirY = -1;
	}
	else if (wantedY > _YPosition)
	{
		*stepDirY = 1;
	}
	else
	{
		*stepDirY = 0;
	}
	// dir in Z-axis
	if (wantedZ < _ZPosition) {
		*stepDirZ = -1;
	}
	else if (wantedZ > _ZPosition)
	{
		*stepDirZ = 1;
	}
	else
	{
		*stepDirZ = 0;
	}
}

/* autor: Maciej Wiecheć
preparing for execution G01
calculating all the data needed for G01 movement
*/
void GCodeInterpreter::LinearMotion_SetUp(float *deltaX, float *stepDirX, float *deltaY, float *stepDirY, float *ai, float *bi, float *d, float *whichCase, float *stepDirZ, int32_t wantedX, int32_t wantedY, int32_t wantedZ) {



	if (wantedZ != _ZPosition) {
		
		if (wantedZ < _ZPosition) {
			*stepDirZ = -1;
		}
		else {
			*stepDirZ = 1;
		}
	}
	else {
		

		if (_XPosition != wantedX || _YPosition != wantedY) {

			if (_XPosition == wantedX) {
				*deltaX = 0;
			}
			else if (_XPosition < wantedX) {
				*stepDirX = 1;
				*deltaX = wantedX - _XPosition;
			}
			else {
				*stepDirX = -1;
				*deltaX = _XPosition - wantedX;
			}


			if (_YPosition == wantedY) {
				*deltaY = 0;
			}
			else if (_YPosition < wantedY) {
				*stepDirY = 1;
				*deltaY = wantedY - _YPosition;
			}
			else {
				*stepDirY = -1;
				*deltaY = _YPosition - wantedY;
			}

			if (*deltaX > *deltaY) {
				*ai = (*deltaY - *deltaX) * 2;
				*bi = *deltaY * 2;
				*d = *bi - *deltaX;
				*whichCase = 1;
			}
			else {
				*ai = (*deltaX - *deltaY) * 2;
				*bi = *deltaX * 2;
				*d = *bi - *deltaY;
				*whichCase = 0;
			}
		}
	}
}

void GCodeInterpreter::G02_SetUp()
{
}

void GCodeInterpreter::G03_SetUp()
{
}

void GCodeInterpreter::Dwell_SetUp()
{
	time = 0;
}

void GCodeInterpreter::GotoBase_SetUp(float* procedure) {
	*procedure = 1; 
}

void GCodeInterpreter::G29_SetUp(float* procedure, float* currentRow, float* currentCol, float *stepDirX, float *stepDirY, float *stepDirZ, float* move, float* setup, float* dX, float* dY)
{
	*procedure = 1;
	*currentRow = 1;
	*currentCol = 1;
	*move = 0;
	*setup = 1;
	arraySizeX = (int)_I;
	arraySizeY = (int)_J;
	PCBsizeX = (_X-10)*_StepsPerMMX;
	PCBsizeY = (_Y-10)*_StepsPerMMY;
	// -10 poniewaz 5mm odpada na uchwyty z kazdej strony
	*LevelArray = (int16_t)realloc(LevelArray, sizeof(int16_t)*arraySizeX*arraySizeY);
	RapidMotion_SetUp(stepDirX, stepDirY, stepDirZ, _BEGINX - PCBsizeX / 2, _BEGINY, _ZPosition);
	*dX = PCBsizeX / (arraySizeX-1);
	*dY = PCBsizeY / (arraySizeY-1);

}

bool GCodeInterpreter::G29_Execute(float* procedure, float* currentRow, float* currentCol, float *stepDirX, float *stepDirY, float *stepDirZ, float* move, float* setup, float* dX, float* dY)
{
	switch ((int)*procedure)
	{
	case 1:
		if (RapidMotion_Execute(stepDirX, stepDirY, stepDirZ, _BEGINX - PCBsizeX / 2, _BEGINY, _ZPosition))
			*procedure = 2;
		break;
	case 2:
		if (*currentRow <= arraySizeX)
		{
			if (*currentCol <= arraySizeY)
			{
				if (*move == 1)
				{
					if (*setup == 1)
					{
						RapidMotion_SetUp(stepDirX, stepDirY, stepDirZ, _XPosition, _YPosition + *dY, _ZPosition);
						*setup = 0;
					}
					else
					{
						if (RapidMotion_Execute(stepDirX, stepDirY, stepDirZ, _XPosition, _YPosition + *dY, _ZPosition))
						{
							*move = 0;
						}
					}
				}
				else
				{
					
					if (ZProbe_Execute())
					{
						*move = 1;
						*setup = 1;
						*currentCol = *currentCol + 1;
					}
				}
			}
			else
			{
				if (*setup == 1)
				{
					RapidMotion_SetUp(stepDirX, stepDirY, stepDirZ, _XPosition + *dX, _BEGINY, _ZPosition);
					*setup = 0;
				}
				else
				{
					if (RapidMotion_Execute(stepDirX, stepDirY, stepDirZ, _XPosition + *dX, _BEGINY, _ZPosition))
					{
						*currentRow = *currentRow + 1;
						*currentCol = 1;
						*move = 0;
					}
				}
			}
		}
		else
		{
			return true;
		}
		return false;
	}
}
void GCodeInterpreter::setPosition_SetUp(float X, float Y, float Z)
{
	_XPosition = X;
	_YPosition = Y;
	_ZPosition = Z;
}

void GCodeInterpreter::setPosition_SetUp(char XYZ, float val)
{
	switch (XYZ)
	{
	case 'X':
	case 'x':
		_XPosition = val;
		break;
	case 'Y':
	case 'y':
		_YPosition = val;
		break;
	case 'Z':
	case 'z':
		_ZPosition = val;
		break;
	}
}

void GCodeInterpreter::SpindleStart_SetUp(float* rotationSpeed)
{
	time = 0;
	*rotationSpeed = BLDC_MINIMUM_SPEED_VALUE;
	_spindleIsWorking = true;
}

void GCodeInterpreter::SpindleStop_SetUp(float* rotationSpeed)
{
	time = 0;
	*rotationSpeed = _SpindleSpeed;
	_spindleIsWorking = false;
}

void GCodeInterpreter::SensorCheck_SetUp(float* procedure, float* procedure1)
{
	randomSeed(analogRead(RANDOM_SEED_1_PIN));
	_X = random(5, 22);
	randomSeed(analogRead(RANDOM_SEED_2_PIN));
	_Y = random(0, 17);
	CalculateSteps();
	*procedure = 1;
	GotoBase_SetUp(procedure1);
}

void GCodeInterpreter::setStepsPerMM_SetUp()
{
	if (_X != DUMMY_VALUE) _StepsPerMMX = _X;
	if (_Y != DUMMY_VALUE) _StepsPerMMY = _Y;
	if (_Z != DUMMY_VALUE) _StepsPerMMZ = _Z;
}

void GCodeInterpreter::saveToEEPROM_SetUp()
{
	uint8_t x1 = _StepsPerMMX >> 8;
	uint8_t x2 = _StepsPerMMX - x1 * 256;
	uint8_t y1 = _StepsPerMMY >> 8;
	uint8_t y2 = _StepsPerMMY - y1 * 256;
	uint8_t z1 = _StepsPerMMZ >> 8;
	uint8_t z2 = _StepsPerMMZ - z1 * 256;
	uint8_t bx1 = _BEGINX >> 8;
	uint8_t bx2 = _BEGINX - bx1 * 256;
	uint8_t by1 = _BEGINY >> 8;
	uint8_t by2 = _BEGINY - by1 * 256;
	
	EEPROM.update(EEPROM_SAVE_PLACE, x1);
	EEPROM.update(EEPROM_SAVE_PLACE + 1, x2);
	EEPROM.update(EEPROM_SAVE_PLACE + 2, y1);
	EEPROM.update(EEPROM_SAVE_PLACE + 3, y2);
	EEPROM.update(EEPROM_SAVE_PLACE + 4, z1);
	EEPROM.update(EEPROM_SAVE_PLACE + 5, z2);
	EEPROM.update(EEPROM_SAVE_PLACE + 6, bx1);
	EEPROM.update(EEPROM_SAVE_PLACE + 7, bx2);
	EEPROM.update(EEPROM_SAVE_PLACE + 8, by1);
	EEPROM.update(EEPROM_SAVE_PLACE + 9, by2);
}

void GCodeInterpreter::readFromEEPROM_SetUp()
{
	int8_t index = EEPROM_SAVE_PLACE;
	uint8_t x1 = EEPROM.read(index); index++; 
	uint8_t x2 = EEPROM.read(index); index++; 
	uint8_t y1 = EEPROM.read(index); index++; 
	uint8_t y2 = EEPROM.read(index); index++; 
	uint8_t z1 = EEPROM.read(index); index++; 
	uint8_t z2 = EEPROM.read(index); index++;
	uint8_t bx1 = EEPROM.read(index); index++;
	uint8_t bx2 = EEPROM.read(index); index++;
	uint8_t by1 = EEPROM.read(index); index++;
	uint8_t by2 = EEPROM.read(index);
	_StepsPerMMX = x1 * 256 + x2;
	_StepsPerMMY = y1 * 256 + y2;
	_StepsPerMMZ = z1 * 256 + z2;
	_BEGINX = bx1 * 256 + bx2;
	_BEGINY = by1 * 256 + by2;
}

void GCodeInterpreter::rotateTable_SetUp() {
	float *temp = &_LV[0];
	float *Endstop = &_LV[1];
	float *Distance = &_LV[2];
	float *Direction = &_LV[3];
	
	*temp = 0;
	*Distance = 0;

	if (Table.returnTablePosition() == 1) {
		*Direction = 1;
		*Endstop = 7;
	}
	else {
		*Direction =  0;
		*Endstop = 6;
	}
}

void GCodeInterpreter::BoardLock_SetUp() {
	float *temp = &_LV[0];
	*temp = 0;
	
}

void GCodeInterpreter::ExecutionIsComplete()
{
	Clear();
	StateMachine.SetIdleState();
	MMcomm.SendReply();
	if (!StateMachine.workInProgress)
	{
		SetSteppersEn(1);
	}
}

void GCodeInterpreter::U12_SetUp(float *stepDirX, float *stepDirY, float *stepDirZ)
{
	RapidMotion_SetUp(stepDirX, stepDirY, stepDirZ, _BEGINX, _BEGINY, _ZPosition);
}

/* autor: Maciej Wiecheć
making single execution of one step of rapid motion
*/
bool GCodeInterpreter::RapidMotion_Execute(float *stepDirX,float *stepDirY, float *stepDirZ, int32_t wantedX, int32_t wantedY, int32_t wantedZ) {
	TCNT1 = RAPID_SPEED;

	/*if ((*stepDirX == -1 && StateMachine.returnEndstop(0))	 ||
		(*stepDirX == 1 && StateMachine.returnEndstop(1))	 ||
		(*stepDirY == -1 && StateMachine.returnEndstop(2))	 ||
		(*stepDirY == 1 && StateMachine.returnEndstop(3))	 ||
		(*stepDirZ == -1 && StateMachine.returnEndstop(4))	 ||
		(*stepDirZ == 1 && StateMachine.returnEndstop(5))	  ) {

		ExecutionIsComplete();

	}*/


	//MMcomm.SendMessage("sen: "+(String)XStepper.GetBoolEnable());
	//Serial.println("_X: " + (String)_X + " _XPoz: " + (String)_XPosition);
	if (CheckMovementPossibility(stepDirX, stepDirY, stepDirZ))
	{
		bool ready = true;
		if (wantedX != _XPosition)
		{
			XStepper.Step(*stepDirX);
			_XPosition += *stepDirX;
			ready = false;
		}
		if (wantedY != _YPosition)
		{
			YStepper.Step(*stepDirY);
			_YPosition += *stepDirY;
			ready = false;
		}
		if (wantedZ != _ZPosition)
		{
			ZStepper.Step(*stepDirZ);
			_ZPosition += *stepDirZ;
			ready = false;
		}
		//if (wantedX == _XPosition && wantedY == _YPosition && wantedZ == _ZPosition)
		if(ready)
		{
			//Command.ExecutionIsComplete();
			return true;
			//StateMachine.SetEndstopsEn(1);
		}
	}
	else
	{
		//Command.ExecutionIsComplete();
		if (StateMachine.returnEndstop(X_MIN_ENDSTOP)) setPosition_SetUp('X', 0);
		if (StateMachine.returnEndstop(Y_MIN_ENDSTOP)) setPosition_SetUp('Y', 0);
		if (StateMachine.returnEndstop(Z_MIN_ENDSTOP)) setPosition_SetUp('Z', 0);
		return true;
	}
	return false;
}

/* autor: Maciej Wiecheć
making single execution of one step in streight line
*/
bool GCodeInterpreter::LinearMotion_Execute(float *deltaX, float *stepDirX, float *deltaY, float *stepDirY, float *ai, float *bi, float *d, float *whichCase, float *stepDirZ, int32_t wantedX, int32_t wantedY, int32_t wantedZ)
{
	TCNT1 = WORKING_SPEED;

	//Serial.println((String)_X + " " + (String)_XPosition + " " + (String)_Y + " " + (String)_YPosition);



	if (wantedZ != _ZPosition)
	{
		ZStepper.Step(*stepDirZ);
		_ZPosition = _ZPosition + *stepDirZ;
		if (wantedZ == _ZPosition)
		{
			//Command.ExecutionIsComplete();
			return true;
		}
	}
	else
	{
		if (*whichCase == 1) {

			if (_XPosition != wantedX) {
				if (*d >= 0) {
					_XPosition = _XPosition + *stepDirX;
					_YPosition = _YPosition + *stepDirY;
					*d = *d + *ai;
					XStepper.Step(*stepDirX);
					YStepper.Step(*stepDirY);
				}
				else {
					*d = *d + *bi;
					_XPosition = _XPosition + *stepDirX;
					XStepper.Step(*stepDirX);
				}
			}
		}
		else {
			if (_YPosition != wantedY) {
				if (*d >= 0) {
					_XPosition = _XPosition + *stepDirX;
					_YPosition = _YPosition + *stepDirY;
					*d = *d + *ai;
					XStepper.Step(*stepDirX);
					YStepper.Step(*stepDirY);
				}
				else {
					*d = *d + *bi;
					_YPosition = _YPosition + *stepDirY;
					YStepper.Step(*stepDirY);
				}
			}
		}
	}
	if (wantedX == _XPosition && wantedY == _YPosition) {
		//Command.ExecutionIsComplete();
		return true;
	}
	return false;
}

bool GCodeInterpreter::G02_Execute()
{
}

bool GCodeInterpreter::G03_Execute()
{
}

bool GCodeInterpreter::Dwell_Execute()
{
	if (time > _P)
	{
		//ExecutionIsComplete();
		return true;
	}
	return false;
}

bool GCodeInterpreter::GotoBase_Execute(float* procedure)
{
	TCNT1 = GO_HOME_SPEED;
	int temp = (int)*procedure;
	//0 - X-Min
	//2 - Y-Min
	//3 - Y-Max

	switch (temp) 
	{
	case 1:
	{
		if (!StateMachine.returnEndstop(Z_MIN_ENDSTOP))
		{
			ZStepper.Step(1);
		}
		else
		{
			_ZPosition = 0;
			*procedure = 2;
		}
	}
	break;

	case 2: {
		if (_ZPosition > -500) {
			ZStepper.Step(-1);
			_ZPosition -= 1;
		}
		else {
			*procedure = 3;
		}
	}
			break;

	case 3: {
		TCNT1 = GO_HOME_SLOW_SPEED;
		if (!StateMachine.returnEndstop(Z_MIN_ENDSTOP)) {
			ZStepper.Step(1);
		}
		else {
			_ZPosition = 0;
			*procedure = 4;
		}
	}
			break;
	case 4: 
	{
		if (!StateMachine.returnEndstop(X_MIN_ENDSTOP)) 
		{
			XStepper.Step(-1);
		}
		else 
		{
			_XPosition = 0;
			*procedure = 5;
		}
	}
			break;

	case 5: {
		if (_XPosition < 500) {
			XStepper.Step(1);
			_XPosition += 1;
		}
		else {
			*procedure = 6;
		}
	}
			break;

	case 6: {
		TCNT1 = GO_HOME_SLOW_SPEED;
		if (!StateMachine.returnEndstop(X_MIN_ENDSTOP)) {
			XStepper.Step(-1);
		}
		else {
			_XPosition = 0;
			*procedure = 7;
		}
	}
			break;

	case 7: {
		if (!StateMachine.returnEndstop(Y_MIN_ENDSTOP)) {
			YStepper.Step(-1);
		}
		else {
			_YPosition = 0;
			*procedure = 8;
		}
	}
			break;

	case 8: {
		if (_YPosition < 1000) {
			YStepper.Step(1);
			_YPosition += 1;
		}
		else {
			*procedure = 9;
		}
	}
			break;

	case 9: {
		TCNT1 = GO_HOME_SLOW_SPEED;
		if (!StateMachine.returnEndstop(Y_MIN_ENDSTOP)) {
			YStepper.Step(-1);
		}
		else {
			_YPosition = 0;
			*procedure = 10;
		}
	}
			break;

	default: {
		////temporary diable the endstops
		//StateMachine.SetEndstopsEn(1);
		//Command.ExecutionIsComplete();
		return true;
	}
			 break;
	}
	return false;
}

bool GCodeInterpreter::ZProbe_Execute()
{
	if (!StateMachine.returnEndstop(TABLE_LEVEL_PROBE))
	{
		ZStepper.Step(-1);
		_ZPosition -= 1;
	}
	else
	{
		_ZProbeValue = _ZPosition;
		return true;
	}
	return false;
}

bool GCodeInterpreter::SpindleStart_Execute(float* rotationSpeed)
{
	if (time > BLDC_ACCELERATION_SPEED)
	{
		if (abs(_SpindleSpeed - *rotationSpeed) > BLDC_ACCELERATION_VALUE)
		{

			*rotationSpeed += BLDC_ACCELERATION_VALUE;
			spindle.setSpeed(*rotationSpeed);
		}
		else
		{
			*rotationSpeed = _SpindleSpeed;
			spindle.setSpeed(*rotationSpeed);
			//ExecutionIsComplete();
			return true;
		}
		time = 0;
	}
	return false;
}

bool GCodeInterpreter::SpindleStop_Execute(float* rotationSpeed)
{
	if (time > BLDC_ACCELERATION_SPEED)
	{
		if (abs(*rotationSpeed - BLDC_MINIMUM_SPEED_VALUE) > BLDC_ACCELERATION_VALUE)
		{
			*rotationSpeed -= BLDC_ACCELERATION_VALUE;
			spindle.setSpeed(*rotationSpeed);
		}
		else
		{
			*rotationSpeed = BLDC_MINIMUM_SPEED_VALUE;
			spindle.setSpeed(*rotationSpeed);
			//ExecutionIsComplete();
			return true;
		}
		time = 0;
	}
	return false;
}

bool GCodeInterpreter::SensorCheck_Execute(float* procedure, float* procedure1, float* stepDirX, float* stepDirY, float* stepDirZ)
{
		switch ((int)*procedure)
		{
		case 1:
			if(GotoBase_Execute(procedure1))
				*procedure = 2;
			break;
		case 2:
			TCNT1 = RAPID_SPEED;
			if (!StateMachine.returnEndstop(TABLE_LEVEL_ENDSTOP))
			{
				ZStepper.Step(-1);
				_ZPosition -= 1;
			}
			else
			{
				_Z = _ZPosition;
				*procedure = 3;
			}
			break;
		case 3:
			if (_ZPosition < _Z + 800)
			{
				ZStepper.Step(1);
				_ZPosition += 1;
			}
			else {
				*procedure = 4;
			}
			break;
		case 4:
			RapidMotion_SetUp(stepDirX, stepDirY, stepDirZ, _XinSTEPS, _YinSTEPS, _ZPosition);
			*procedure = 5;
			break;
		case 5:
			if (RapidMotion_Execute(stepDirX, stepDirY, stepDirZ, _XinSTEPS, _YinSTEPS, _ZPosition))
				*procedure = 6;
			break;
		case 6:
			if (_ZPosition > _Z - LEVEL_SENSOR_DELTA)
			{
				if (ZProbe_Execute())
				{
					*procedure = 7;
					_SensorIsWorking = true;
				}
					
			}
			else
			{
				*procedure = 7;
				_SensorIsWorking = false;
			}
			break;
		case 7:
			GotoBase_SetUp(procedure1);
			*procedure = 8;
			break;
		case 8:
			if (GotoBase_Execute(procedure1))
				*procedure = 9;
			break;
		default:
			if (!_SensorIsWorking)
			{
				StateMachine.SetErrorState(SENSOR_ERROR);
				return false;
			}
			return true;
			break;
		}
		
	return false;
}

bool GCodeInterpreter::rotateTable_Execute() {
	TCNT1 = RPS0_25;
	float *temp = &_LV[0];
	float *Endstop = &_LV[1];
	float *Distance = &_LV[2];
	float *Direction = &_LV[3];

	//MMcomm.SendMessage("dist: " + (String)*Distance + " temp: " + (String)*temp + " endstop: " + (String)!Table.returnTablePosition());
	
	if (*Distance < 6000) {
		Table.holder.Step(-1);
		*Distance = *Distance + 1;
	}
	else {
		
		if (StateMachine.returnEndstop(*Endstop) == 0) {
			if (*Direction) Table.rotateClockwise();
			else Table.rotateCounterClockwise();

			//MMcomm.SendMessage("rotation");
		}
		else {
			//MMcomm.SendMessage("closing");
			if (*temp == 349) {
				Table.holder.SetEnable(0);
				Table.setTablePosition(!Table.returnTablePosition());
			}

			Table.stop();
			boardLock_Execute();
		}
	}

	
}

bool GCodeInterpreter::boardLock_Execute() {
	TCNT1 = RPS0_25;
	float *temp = &_LV[0];

	int sum = (StateMachine.returnEndstop(8) + StateMachine.returnEndstop(9) +
		StateMachine.returnEndstop(10) + StateMachine.returnEndstop(11))*(
			StateMachine.returnEndstop(12) + StateMachine.returnEndstop(13) +
			StateMachine.returnEndstop(14) + StateMachine.returnEndstop(15));

	if (sum) {

		if(*temp<350){
			Table.holder.Step(1);
			*temp = *temp + 1;
		}
		else {
			MMcomm.SendMessage("end");
			MMcomm.SendReply();
			Table.holder.SetEnable(1);
			Clear();
			MMcomm.SendMessage("dist: " + (String)_LV[2] + " temp: " + (String)_LV[0] + " endstop: " + (String)!Table.returnTablePosition());
			StateMachine.SetIdleState();
		}

	}
	else {
		Table.holder.Step(1);
	}
}

bool GCodeInterpreter::boardUnlock_Execute() {
	TCNT1 = RPS0_25;
	if (StateMachine.returnEndstop(16)) {
		StateMachine.SetIdleState();
		MMcomm.SendReply();
		Table.holder.SetEnable(1);
	}
	else {
		Table.holder.Step(-1);
	}
}

bool GCodeInterpreter::U12_Execute(float *stepDirX, float *stepDirY, float *stepDirZ)
{
	RapidMotion_Execute(stepDirX, stepDirY, stepDirZ, _BEGINX, _BEGINY, _ZPosition);
}

/* autor: Bartek Kudroń
funkcja wykonywana co krok programu, w zależności od komendy różny kod.
*/
void GCodeInterpreter::ExecuteStep()
{

	//			G COMMANDS

	switch ((int)_G)
	{
	case 0:
		if (RapidMotion_Execute(&_LV[0], &_LV[1], &_LV[2], _XinSTEPS, _YinSTEPS, _ZinSTEPS))
			ExecutionIsComplete();
		break;
	case 1:
		if (LinearMotion_Execute(&_LV[0], &_LV[1], &_LV[2], &_LV[3], &_LV[4], &_LV[5], &_LV[6], &_LV[7], &_LV[8], _XinSTEPS, _YinSTEPS, _ZinSTEPS))
			ExecutionIsComplete();
		break;
	case 2: //G02 command - to be filled

		break;
	case 3: //G03 command - to be filled

		break;
	case 4:
		if (Dwell_Execute())
			ExecutionIsComplete();
		break;
	case 20:
		ExecutionIsComplete();
		break;
	case 21:
		ExecutionIsComplete();
		break;
	case 28:
		if (GotoBase_Execute(&_LV[0]))
			ExecutionIsComplete();
		break;
	case 29:
		if (G29_Execute(&_LV[0], &_LV[1], &_LV[2], &_LV[3], &_LV[4], &_LV[5], &_LV[6], &_LV[7], &_LV[8], &_LV[9]))
			ExecutionIsComplete();
	case 30:
		if (ZProbe_Execute())
			ExecutionIsComplete();
		break;
	case 90:
		ExecutionIsComplete();
		break;
	case 91:
		ExecutionIsComplete();
		break;
	case 92:
		ExecutionIsComplete();
		break;
	default:




		//			M COMMANDS




		switch ((int)_M)
		{
		case 3: 
			if (SpindleStart_Execute(&_LV[0]))
				ExecutionIsComplete();
			break;
		case 4: 
			if (SpindleStart_Execute(&_LV[0]))
				ExecutionIsComplete();
			break;
		case 5: 
			if (SpindleStop_Execute(&_LV[0]))
				ExecutionIsComplete();
			break;
		case 48:
			if (SensorCheck_Execute(&_LV[0], &_LV[1], &_LV[2], &_LV[3], &_LV[4]))
				ExecutionIsComplete();
			break;
		case 92:
			ExecutionIsComplete();
			break;
		case 500:
			ExecutionIsComplete();
			break;
		case 501:
			ExecutionIsComplete();
			break;
		default:


			//		U COMMANDS


			switch ((int)_U)
			{
			case 0:
				rotateTable_Execute();
				break;
			case 1: 
				boardLock_Execute();
				break;
			case 2:
				boardUnlock_Execute();
				break;
			case 11: //U03 command - to be filled
				ExecutionIsComplete();
				break;
			case 12:
				if (U12_Execute(&_LV[0], &_LV[1], &_LV[2]))
					ExecutionIsComplete();
				break;
			default:
				if (_S != DUMMY_VALUE)
				{
					if (_spindleIsWorking)
					{
						if (time > BLDC_ACCELERATION_SPEED)
						{
							time = 0;
							if (_S > _SpindleSpeed)
							{
								if (_S - _SpindleSpeed > BLDC_ACCELERATION_VALUE)
								{
									_SpindleSpeed += BLDC_ACCELERATION_VALUE;
									spindle.setSpeed(_SpindleSpeed);
								}
								else
								{
									_SpindleSpeed = _S;
									spindle.setSpeed(_SpindleSpeed);
									ExecutionIsComplete();
								}

							}
							else
							{
								if (_SpindleSpeed - _S > BLDC_ACCELERATION_VALUE)
								{
									_SpindleSpeed -= BLDC_ACCELERATION_VALUE;
									spindle.setSpeed(_SpindleSpeed);
								}
								else
								{
									_SpindleSpeed = _S;
									spindle.setSpeed(_SpindleSpeed);
									ExecutionIsComplete();
								}
							}

						}

					}
					else
					{
						ExecutionIsComplete();
					}
				}
				else
				{
					// ERROR
					//MMcomm.SendMessage("ERROR. UNKNOWN COMMAND");
					StateMachine.SetErrorState(UNKNOWN_GCODE_ERROR);
					Clear();

				}
				break;
			}
			break;
		}
		break;
	};
}

/* autor: Bartek Kudroń
funkcja wykonywana przed rozpoczęciem pętli komendy. wykonywana raz, kod różny w zależności od komendy.
*/
void GCodeInterpreter::PrepareForExecution()
{
	//			G COMMANDS
	SetSteppersEn(0);
	switch ((int)_G)
	{
	case 0:
		CalculateSteps();
		RapidMotion_SetUp(&_LV[0], &_LV[1], &_LV[2], _XinSTEPS, _YinSTEPS, _ZinSTEPS);

		//temporary disable the endstops
	//	StateMachine.SetEndstopsEn(0);
		//SetSteppersEn(0);

		/*
		for (int i = 0; i < 20; i++) {
			MMcomm.SendMessage("stycznik " + (String)i+" "+(String)StateMachine.returnEndstop(i));
		}
		MMcomm.SendMessage("xen: " + (String)XStepper.GetBoolEnable());
		MMcomm.SendMessage("yen: " + (String)YStepper.GetBoolEnable());
		MMcomm.SendMessage("zen: " + (String)ZStepper.GetBoolEnable());
		*/

		break;
	case 1:
		CalculateSteps();
		LinearMotion_SetUp(&_LV[0], &_LV[1], &_LV[2], &_LV[3], &_LV[4], &_LV[5], &_LV[6], &_LV[7], &_LV[8], _XinSTEPS, _YinSTEPS, _ZinSTEPS);

		//temporary disable the endstops
		//StateMachine.SetEndstopsEn(0);
		//SetSteppersEn(0);
		break;
	case 2: //G02 command - to be filled

		break;
	case 3: //G03 command - to be filled

		break;
	case 4:
		Dwell_SetUp();
		break;
	case 20:
		_unitsMM = false;
		break;
	case 21:
		_unitsMM = true;
		break;
	case 28:
		GotoBase_SetUp(&_LV[0]);
		//SetSteppersEn(0);
		break;
	case 29:
		G29_SetUp(&_LV[0], &_LV[1], &_LV[2], &_LV[3], &_LV[4], &_LV[5], &_LV[6], &_LV[7], &_LV[8], &_LV[9]);
	case 30:
		TCNT1 = RAPID_SPEED;
		break;
	case 90:
		_AbsoluteMotion = true;
		break;
	case 91:
		_AbsoluteMotion = false;
		break;
	case 92:
		if (_X != DUMMY_VALUE) setPosition_SetUp('X', _X);
		if (_Y != DUMMY_VALUE) setPosition_SetUp('Y', _Y);
		if (_Z != DUMMY_VALUE) setPosition_SetUp('Z', _Z);
		break;
	default:




		//			M COMMANDS




		switch ((int)_M)
		{
		case 3:
			SpindleStart_SetUp(&_LV[0]);
			break;
		case 4:
			SpindleStart_SetUp(&_LV[0]);
			break;
		case 5:
			SpindleStop_SetUp(&_LV[0]);
			break;
		case 48:
			SensorCheck_SetUp(&_LV[0], &_LV[1]);
			break;
		case 92:
			setStepsPerMM_SetUp();
			break;
		case 500:
			saveToEEPROM_SetUp();
			break;
		case 501:
			readFromEEPROM_SetUp();
			break;
		default:



			//		U COMMANDS




			switch ((int)_U)
			{

			case 0: 
				Table.holder.SetEnable(0);
				rotateTable_SetUp();
				
				break;
			case 1: 
				BoardLock_SetUp();
				Table.holder.SetEnable(0);
				break;
			case 2: 
				Table.holder.SetEnable(0);
				break;
			case 11:
				_BEGINX = _X;
				_BEGINY = _Y;
				break;
			case 12:
				U12_SetUp(&_LV[0], &_LV[1], &_LV[2]);
			default:
				if (_S != DUMMY_VALUE)
				{
					if (_spindleIsWorking)
					{
						time = 0;
					}
					else
					{
						_SpindleSpeed == _S;
					}
				}
				else
				{
					// ERROR
					StateMachine.SetErrorState(UNKNOWN_GCODE_ERROR);
					ExecutionIsComplete();
					Clear();

				}
				break;
			}
		}
	}


}

/* autor: Bartek Kudroń
funkcja wyciągająca ze stringa wartości dla konkretnych liter.
*/
bool GCodeInterpreter::Interpret(String command)
{
	bool success = true;
	float *currentLetter;
	String number = "";
	if (command == "") success = false;

	for (int i = 0; i < command.length(); i++)
	{
		switch (command[i])
		{
		case 'G':
			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_G;
			break;

		case 'X':

			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_X;
			break;

		case 'Y':
			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_Y;
			break;

		case 'Z':
			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_Z;
			break;

		case 'I':
			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_I;
			break;

		case 'J':
			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_J;
			break;

		case 'M':
			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_M;
			break;

		case 'S':
			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_S;
			break;

		case 'F':
			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_F;
			break;
		case 'U':

			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_U;
			break;
		case 'P':

			if (number != "")
			{
				*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE)*POSITION_ACCURACY;
				number = "";
			}
			currentLetter = &_P;
			break;

		default:
			if (((int)command[i] - '0' >= 0 && (int)command[i] - '0' <= 9) || command[i] == '.' || command[i] == ',' || command[i] == '-')
				if (command[i] == ',') {
					number += '.';
				}
				else number += command[i];
			else
			{

				success = false;
			}
			break;
		}
	}


	if (number != "")
	{
		//MMcomm.SendMessage(number);
		//MMcomm.SendMessage(String(number.toFloat()));
		*currentLetter = round(number.toFloat()*POSITION_ACCURACY_INVERSE);
		//MMcomm.SendMessage(String(*currentLetter));
		*currentLetter *= POSITION_ACCURACY;
		//MMcomm.SendMessage(String(*currentLetter));
	}
	if (!success)
	{
		MMcomm.SendMessage(INTERPRETATION_FAILED_WARNING);
	}

	// jeśli nie podana była żadna wartość w komendzie to niech 
	// docelowa wartość będzie taka jak aktualna. Nie będzie wtedy ruchu
	if (_X == DUMMY_VALUE) _X = _XPosition;
	if (_Y == DUMMY_VALUE) _Y = _YPosition;
	if (_Z == DUMMY_VALUE) _Z = _ZPosition;

	//MMcomm.SendMessage("G: " + (String)_G);
	//MMcomm.SendMessage("X: " + (String)_X + " Y: " + (String)_Y + " Z: " + (String)_Z);
	//MMcomm.SendMessage("Xpoz: " + (String)_XPosition + " Ypoz: " + (String)_YPosition + " Zpoz: " + (String)_ZPosition);
	return success;
}

void GCodeInterpreter::CalculateSteps()
{
	float x = _X;
	float y = _Y;
	float z = _Z;
	//_XinSTEPS = _X * POSITION_ACCURACY_INVERSE;
	//_YinSTEPS = _Y * POSITION_ACCURACY_INVERSE;
	//_ZinSTEPS = _Z * POSITION_ACCURACY_INVERSE;
	if (!_unitsMM)
	{
		x *= INCH_TO_MM;
		y *= INCH_TO_MM;
		z *= INCH_TO_MM;
		//_XinSTEPS *= INCH_TO_MM;
		//_YinSTEPS *= INCH_TO_MM;
		//_ZinSTEPS *= INCH_TO_MM;
	}
	_XinSTEPS = x * _StepsPerMMX;
	_YinSTEPS = y * _StepsPerMMY;
	_ZinSTEPS = z * _StepsPerMMZ;
	//_XinSTEPS *= _StepsPerMMX * POSITION_ACCURACY;
	//_YinSTEPS *= _StepsPerMMY * POSITION_ACCURACY;
	//_ZinSTEPS *= _StepsPerMMZ * POSITION_ACCURACY;
}

bool GCodeInterpreter::CheckMovementPossibility(float* stepDirX, float* stepDirY, float* stepDirZ)
{
	if (((*stepDirX == -1) && (StateMachine.returnEndstop(X_MIN_ENDSTOP))) ||
		((*stepDirX ==  1) && (StateMachine.returnEndstop(X_MAX_ENDSTOP))) ||
		((*stepDirY == -1) && (StateMachine.returnEndstop(Y_MIN_ENDSTOP))) ||
		((*stepDirY ==  1) && (StateMachine.returnEndstop(Y_MAX_ENDSTOP))) ||
		((*stepDirZ ==  1) && (StateMachine.returnEndstop(Z_MIN_ENDSTOP))) ||
		((*stepDirZ == -1) && (StateMachine.returnEndstop(Z_MAX_ENDSTOP) ||
							   StateMachine.returnEndstop(TABLE_LEVEL_ENDSTOP) ||
							   StateMachine.returnEndstop(TABLE_LEVEL_PROBE))))
	{
		//MMcomm.SendMessage(String((*stepDirX == -1) && (StateMachine.returnEndstop(X_MIN_ENDSTOP))));
		return false;
	}
	return true;
}