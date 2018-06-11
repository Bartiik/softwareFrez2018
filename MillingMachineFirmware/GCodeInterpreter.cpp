#include "GCodeInterpreter.h"
#include "Communication.h"
#include "MMStateMachine.h"
#include "SMotor.h"
#include "BLDCDriver.h"
GCodeInterpreter Command;

GCodeInterpreter::GCodeInterpreter()
{
	_XPosition = 0;
	_YPosition = 0;
	_ZPosition = 0;
	_SpindleSpeed = BLDC_DEFAULT_SPEED;
	_spindleIsWorking = false;
	Clear();
}

GCodeInterpreter::~GCodeInterpreter() {}

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

void GCodeInterpreter::SetSteppersEn(bool EN) {
	XStepper.SetEnable(EN);
	YStepper.SetEnable(EN);
	ZStepper.SetEnable(EN);
}

/* autor: Maciej Wiecheć
preparing for execution G00
set dir for each axis
*/
void GCodeInterpreter::G00_SetUp() {
	float *stepDirX = &_LV[0];
	float *stepDirY = &_LV[1];
	float *stepDirZ = &_LV[2];

	// dir in X-axis
	if (_X < _XPosition) {
		*stepDirX = -1;
	}
	else {
		*stepDirX = 1;
	}
	// dir in Y-axis
	if (_Y < _YPosition) {
		*stepDirY = -1;
	}
	else {
		*stepDirY = 1;
	}
	// dir in Z-axis
	if (_Z < _ZPosition) {
		*stepDirZ = -1;
	}
	else {
		*stepDirZ = 1;
	}
}



/* autor: Maciej Wiecheć
preparing for execution G01
calculating all the data needed for G01 movement
*/
void GCodeInterpreter::G01_SetUp() {



	if (_Z != _ZPosition) {
		float *stepDirZ = &_LV[8];
		if (_Z < _ZPosition) {
			*stepDirZ = -1;
		}
		else {
			*stepDirZ = 1;
		}
	}
	else {
		float *deltaX = &_LV[0];
		float *stepDirX = &_LV[1];
		float *deltaY = &_LV[2];
		float *stepDirY = &_LV[3];
		float *ai = &_LV[4];
		float *bi = &_LV[5];
		float *d = &_LV[6];
		float *wchichCase = &_LV[7];

		if (_XPosition != _X || _YPosition != _Y) {

			if (_XPosition == _X) {
				*stepDirX = 0;
				*deltaX = 0;
			}
			else if (_XPosition < _X) {
				*stepDirX = 1;
				*deltaX = _X - _XPosition;
			}
			else {
				*stepDirX = -1;
				*deltaX = _XPosition - _X;
			}


			if (_YPosition == _Y) {
				*stepDirY = 0;
				*deltaY = 0;
			}
			else if (_YPosition < _Y) {
				*stepDirY = 1;
				*deltaY = _Y - _YPosition;
			}
			else {
				*stepDirY = -1;
				*deltaY = _YPosition - _Y;
			}

			if (*deltaX > *deltaY) {
				*ai = (*deltaY - *deltaX) * 2;
				*bi = *deltaY * 2;
				*d = *bi - *deltaX;
				*wchichCase = 1;
			}
			else {
				*ai = (*deltaX - *deltaY) * 2;
				*bi = *deltaX * 2;
				*d = *bi - *deltaY;
				*wchichCase = 0;
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

void GCodeInterpreter::G04_SetUp()
{
	time = 0;
}
void GCodeInterpreter::G28_SetUp() {
	float *procedure = &_LV[0];

	*procedure = 1;
	StateMachine.SetEndstopsEn(0);

}

void GCodeInterpreter::M03_SetUp()
{
	time = 0;
	MMcomm.SendMessage((String)_SpindleSpeed);
	_LV[0] = BLDC_MINIMUM_SPEED_VALUE;
	_spindleIsWorking = true;
}

void GCodeInterpreter::M05_SetUp()
{
	time = 0;
	MMcomm.SendMessage((String)_SpindleSpeed);
	_LV[0] = _SpindleSpeed;
	_spindleIsWorking = false;
}

void GCodeInterpreter::ExecutionIsComplete()
{
	//MMcomm.SendMessage("MOVEMENT END " );
	//MMcomm.SendMessage("Xpoz: " + (String)_XPosition + " Ypoz: " + (String)_YPosition + " Zpoz: " + (String)_ZPosition);

	Clear();
	StateMachine.SetIdleState();
	MMcomm.SendReply();
	SetSteppersEn(1);
}
/* autor: Maciej Wiecheć
making single execution of one step of rapid motion
*/

void GCodeInterpreter::G00_Execute() {
	float *stepDirX = &_LV[0];
	float *stepDirY = &_LV[1];
	float *stepDirZ = &_LV[2];
	TCNT1 = RAPID_SPEED;
	//MMcomm.SendMessage("sen: "+(String)XStepper.GetBoolEnable());
	//Serial.println("_X: " + (String)_X + " _XPoz: " + (String)_XPosition);
	if (_X != _XPosition) {
		XStepper.Step(*stepDirX);
		_XPosition += *stepDirX;
	}
	if (_Y != _YPosition) {
		YStepper.Step(*stepDirY);
		_YPosition += *stepDirY;
	}
	if (_Z != _ZPosition) {
		ZStepper.Step(*stepDirZ);
		_ZPosition += *stepDirZ;
	}

	if (_X == _XPosition && _Y == _YPosition && _Z == _ZPosition) {
		Command.ExecutionIsComplete();
	}

}

/* autor: Maciej Wiecheć
making single execution of one step in streight line
*/
void GCodeInterpreter::G01_Execute()
{
	TCNT1 = WORKING_SPEED;

	//Serial.println((String)_X + " " + (String)_XPosition + " " + (String)_Y + " " + (String)_YPosition);



	if (_Z != _ZPosition)
	{
		float *stepDirZ = &_LV[8];
		ZStepper.Step(*stepDirZ);
		_ZPosition = _ZPosition + *stepDirZ;
		if (_Z == _ZPosition)
		{
			Command.ExecutionIsComplete();
		}
	}
	else
	{
		float *deltaX = &_LV[0];
		float *stepDirX = &_LV[1];
		float *deltaY = &_LV[2];
		float *stepDirY = &_LV[3];
		float *ai = &_LV[4];
		float *bi = &_LV[5];
		float *d = &_LV[6];
		float *wchichCase = &_LV[7];


		if (*wchichCase == 1) {

			if (_XPosition != _X) {
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
			if (_YPosition != _Y) {
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
	if (_X == _XPosition && _Y == _YPosition) {
		Command.ExecutionIsComplete();
	}
}

void GCodeInterpreter::G02_Execute()
{
}

void GCodeInterpreter::G03_Execute()
{
}

void GCodeInterpreter::G28_Execute()
{
	float *procedure = &_LV[0];
	TCNT1 = GO_HOME_SPEED;
	int temp = (int)*procedure;



	//0 - X-Min
	//2 - Y-Min
	//3 - Y-Max

	switch (temp) {

	case 1: {
		if (StateMachine.returnEndstop(0) == 0) {
			XStepper.Step(-1);
		}
		else {
			_XPosition = 0;
			*procedure = 2;
		}
	}
			break;

	case 2: {
		if (_XPosition < 1000) {
			XStepper.Step(1);
			_XPosition += 1;
		}
		else {
			*procedure = 3;
		}
	}
			break;

	case 3: {
		TCNT1 = GO_HOME_SLOW_SPEED;
		if (StateMachine.returnEndstop(0) == 0) {
			XStepper.Step(-1);
		}
		else {
			_XPosition = 0;
			*procedure = 4;
		}
	}
			break;

	case 4: {
		if (StateMachine.returnEndstop(2) == 0) {
			YStepper.Step(-1);
		}
		else {
			_YPosition = 0;
			*procedure = 5;
		}
	}
			break;

	case 5: {
		if (_YPosition < 1000) {
			YStepper.Step(1);
			_YPosition += 1;
		}
		else {
			*procedure = 6;
		}
	}
			break;

	case 6: {
		TCNT1 = GO_HOME_SLOW_SPEED;
		if (StateMachine.returnEndstop(2) == 0) {
			YStepper.Step(-1);
		}
		else {
			_YPosition = 0;
			*procedure = 7;
		}
	}
			break;

	case 7: {
		////temporary diable the endstops
		//StateMachine.SetEndstopsEn(1);
		Command.ExecutionIsComplete();
	}
			break;
	}
}

void GCodeInterpreter::G04_Execute()
{
	if (time > _P)
	{
		ExecutionIsComplete();
	}
}

void GCodeInterpreter::M03_Execute()
{
	if (time > BLDC_ACCELERATION_SPEED)
	{
		if (abs(_SpindleSpeed - _LV[0]) > BLDC_ACCELERATION_VALUE)
		{

			_LV[0] += BLDC_ACCELERATION_VALUE;
			spindle.setSpeed(_LV[0]);
		}
		else
		{
			_LV[0] = _SpindleSpeed;
			spindle.setSpeed(_LV[0]);
			ExecutionIsComplete();
		}
		time = 0;
	}
}

void GCodeInterpreter::M05_Execute()
{
	if (time > BLDC_ACCELERATION_SPEED)
	{
		if (abs(_LV[0] - BLDC_MINIMUM_SPEED_VALUE) > BLDC_ACCELERATION_VALUE)
		{
			_LV[0] -= BLDC_ACCELERATION_VALUE;
			spindle.setSpeed(_LV[0]);
		}
		else
		{
			_LV[0] = BLDC_MINIMUM_SPEED_VALUE;
			spindle.setSpeed(_LV[0]);
			ExecutionIsComplete();
		}
		time = 0;
	}
}

void GCodeInterpreter::U00_Execute()
{
}

void GCodeInterpreter::U01_Execute() {
	 
}

void GCodeInterpreter::U02_Execute() {
	 
}

void GCodeInterpreter::U03_Execute() {
	 
}

/* autor: Bartek Kudroń
funkcja wykonywana co krok programu, w zależności od komendy różny kod.
*/
void GCodeInterpreter::ExecuteStep()
{

	//			G COMMANDS

	switch ((int)_G)
	{
	case 0: //G00 command - to be filled
		G00_Execute();
		break;
	case 1: //G01 command - to be filled
		G01_Execute();

		break;
	case 2: //G02 command - to be filled

		break;
	case 3: //G03 command - to be filled

		break;
	case 4: //G04 command - to be filled
		G04_Execute();
		break;
	case 28: //G28 command - to be filled
		G28_Execute();
		break;
	default:




		//			M COMMANDS




		switch ((int)_M)
		{
		case 3: //M03 command - to be filled
			M03_Execute();
			break;
		case 4: //M04 command - to be filled
			M03_Execute();
			break;
		case 5: //M05 command - to be filled
			M05_Execute();
			break;
		default:


			//		U COMMANDS


			switch ((int)_U)
			{

			case 0: //U00 command - to be filled

				break;
			case 1: //U01 command - to be filled

				break;
			case 2: //U02 command - to be filled

				break;
			case 3: //U03 command - to be filled

				break;
			default:
				if (_S != DUMMY_VALUE)
				{
					if (_spindleIsWorking)
					{
						if (time > 100)
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
					MMcomm.SendMessage("ERROR. UNKNOWN COMMAND");
					StateMachine.SetErrorState();
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

	switch ((int)_G)
	{
	case 0: //G00 command - to be filled
		G00_SetUp();

		//temporary diable the endstops
	//	StateMachine.SetEndstopsEn(0);
		SetSteppersEn(0);

		/*
		for (int i = 0; i < 20; i++) {
			MMcomm.SendMessage("stycznik " + (String)i+" "+(String)StateMachine.returnEndstop(i));
		}
		MMcomm.SendMessage("xen: " + (String)XStepper.GetBoolEnable());
		MMcomm.SendMessage("yen: " + (String)YStepper.GetBoolEnable());
		MMcomm.SendMessage("zen: " + (String)ZStepper.GetBoolEnable());
		*/

		break;
	case 1: //G01 command - to be filled
		G01_SetUp();

		//temporary diable the endstops
		StateMachine.SetEndstopsEn(0);
		SetSteppersEn(0);
		break;
	case 2: //G02 command - to be filled

		break;
	case 3: //G03 command - to be filled

		break;
	case 4: //G04 command - to be filled
		G04_SetUp();
		break;
	case 28: //G28 command - to be filled
		G28_SetUp();
		SetSteppersEn(0);
		break;
	default:




		//			M COMMANDS




		switch ((int)_M)
		{
		case 3: //M03 command - to be filled
			M03_SetUp();
			break;
		case 4: //M04 command - to be filled
			M03_SetUp();
			break;
		case 5: //M05 command - to be filled
			M05_SetUp();
			break;
		default:



			//		U COMMANDS




			switch ((int)_U)
			{

			case 0: //U00 command - to be filled

				break;
			case 1: //U01 command - to be filled
				TableStepper.SetEnable(0);
				break;
			case 2: //U02 command - to be filled

				break;
			case 3: //U03 command - to be filled

				break;
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
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_G;
			break;

		case 'X':

			if (number != "")
			{
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_X;
			break;

		case 'Y':
			if (number != "")
			{
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_Y;
			break;

		case 'Z':
			if (number != "")
			{
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_Z;
			break;

		case 'I':
			if (number != "")
			{
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_I;
			break;

		case 'J':
			if (number != "")
			{
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_J;
			break;

		case 'M':
			if (number != "")
			{
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_M;
			break;

		case 'S':
			if (number != "")
			{
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_S;
			break;

		case 'F':
			if (number != "")
			{
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_F;
			break;
		case 'U':

			if (number != "")
			{
				*currentLetter = number.toFloat();
				number = "";
			}
			currentLetter = &_U;
			break;
		case 'P':

			if (number != "")
			{
				*currentLetter = number.toFloat();
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
		*currentLetter = number.toFloat();
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