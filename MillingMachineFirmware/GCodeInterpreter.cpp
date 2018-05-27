#include "GCodeInterpreter.h"
#include "Communication.h"
#include "MMStateMachine.h"
#include "SMotor.h"
GCodeInterpreter Command;

GCodeInterpreter::GCodeInterpreter()
{
	Clear();
}

GCodeInterpreter::~GCodeInterpreter(){}

/* autor: Bartek Kudroń
wyczyszczenie danych zawartych w klasie
*/
void GCodeInterpreter::Clear()
{
	_G = DUMMY_VALUE;
	_M = DUMMY_VALUE;
	_X = 0;
	_Y = 0;
	_Z = 0;
	_I = DUMMY_VALUE;
	_J = DUMMY_VALUE;
	_S = DUMMY_VALUE;
	_F = DUMMY_VALUE;
	_U = DUMMY_VALUE;
	_XPosition = 0;
	_YPosition = 0;
	_ZPosition = 0;
	_isFinished = 0;
}

/* autor: Maciej Wiecheć
preparing for execution G01
calculating all the data needed for G01 movement
*/
void GCodeInterpreter::G01_SetUp() {
	

	if (_XPosition == _X && _YPosition == _Y) {
		_isFinished = 1;
	}
	else {
		_isFinished = 0;
		if (_XPosition == _X) {
			_LV[1] = 0;
			_LV[0] = 0;
		}
		else if (_XPosition < _X) {
			_LV[1] = 1;
			_LV[0] = _X - _XPosition;
		}
		else {
			_LV[1] = -1;
			_LV[0] = _XPosition - _X;
		}


		if (_YPosition == _Y) {
			_LV[3] = 0;
			_LV[2] = 0;
		}
		else if (_YPosition < _Y) {
			_LV[3] = 1;
			_LV[2] = _Y - _YPosition;
		}
		else {
			_LV[3] = -1;
			_LV[2] = _YPosition - _Y;
		}

		if (_LV[0] > _LV[2]) {
			_LV[4] = (_LV[2] - _LV[0]) * 2;
			_LV[5] = _LV[2] * 2;
			_LV[6] = _LV[5] - _LV[0];
			_LV[7] = 1;
		}
		else {
			_LV[4] = (_LV[0] - _LV[2]) * 2;
			_LV[5] = _LV[0] * 2;
			_LV[6] = _LV[5] - _LV[2];
			_LV[7] = 0;
		}
	}
}


void GCodeInterpreter::ExecutionIsComplete()
{
	Clear();
	MMcomm.SendReply();
	StateMachine.SetIdleState();
}
/* autor: Maciej Wiecheć
making single execution of one step in streight line
*/
void GCodeInterpreter::G01_Execute() {
	TCNT1 = RPS2_5;

	if (StateMachine.CurrentState()!= EXECUTION_STATE) {
		XStepper.SetEnable(1);
		YStepper.SetEnable(1);
//		ZStepper.SetEnable(1);
	}
	else {

		if (_LV[7] == 1) {

			if (_XPosition != _X) {
				if (_LV[6] >= 0) {
					_XPosition = _XPosition + _LV[1];
					_YPosition = _YPosition + _LV[3];
					_LV[6] = _LV[6] + _LV[4];
					XStepper.Step(_LV[1]);
					YStepper.Step(_LV[3]);
				}
				else {
					_LV[6] = _LV[6] + _LV[5];
					_XPosition = _XPosition + _LV[1];
					XStepper.Step(_LV[1]);
				}
			}
		}
		else {
			if (_YPosition != _Y) {
				if (_LV[6] >= 0) {
					_XPosition = _XPosition + _LV[1];
					_YPosition = _YPosition + _LV[3];
					_LV[6] = _LV[6] + _LV[4];
					XStepper.Step(_LV[1]);
					YStepper.Step(_LV[3]);
				}
				else {
					_LV[6] = _LV[6] + _LV[5];
					_YPosition = _YPosition + _LV[3];
					YStepper.Step(_LV[3]);
				}
			}
		}
	}
	if (_X == _XPosition && _Y == _YPosition) { 
		_isFinished = 1;	
	}
}

bool GCodeInterpreter::IsExecutionFinished() {
	return _isFinished;
}



/* autor: Bartek Kudroń
funkcja wykonywana co krok programu, w zależności od komendy różny kod.
*/
void GCodeInterpreter::ExecuteStep()
{
	
	/*if (newCommand)
	{
		newCommand = false;
	}
	*/

	//			G COMMANDS

	switch ((int)_G)
	{
	case 0: //G00 command - to be filled

		break;
	case 1: //G01 command - to be filled
		G01_Execute();
		break;
	case 2: //G02 command - to be filled

		break;
	case 3: //G03 command - to be filled

		break;
	case 4: //G04 command - to be filled

		break;
	case 28: //G28 command - to be filled

		break;
	default:




		//			M COMMANDS




		switch ((int)_M)
		{
		case 3: //M03 command - to be filled

			break;
		case 4: //M04 command - to be filled

			break;
		case 5: //M05 command - to be filled

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

				// ERROR
				MMcomm.SendMessage("ERROR. UNKNOWN COMMAND");
				StateMachine.SetErrorState();
				Clear();
				break;
			}
		}
	}
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

		break;
	case 1: //G01 command - to be filled
		G01_SetUp();
		break;
	case 2: //G02 command - to be filled

		break;
	case 3: //G03 command - to be filled

		break;
	case 4: //G04 command - to be filled

		break;
	case 28: //G28 command - to be filled

		break;
	default:




		//			M COMMANDS




		switch ((int)_M)
		{
		case 3: //M03 command - to be filled

			break;
		case 4: //M04 command - to be filled

			break;
		case 5: //M05 command - to be filled

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
				
				// ERROR
				MMcomm.SendMessage("ERROR. UNKNOWN COMMAND");
				StateMachine.SetErrorState();
				Clear();
				break;
			}
		}
	}
}


/* autor: Bartek Kudroń
funkcja wyciągająca ze stringa wartości dla konkretnych liter.
*/
void GCodeInterpreter::Interpret(String command)
{
	float *currentLetter;
	String number = "";
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
		
		default:
			if ( ((int)command[i] - '0' >= 0 && (int)command[i] - '0' <= 9) || command[i] == '.' || command[i] == ',' || command[i] == '-')
				if (command[i] == ',') {
					number += '.';
				}
				else number += command[i];
			break;
		}

		
	}
	
	if (number != "")
	{
		*currentLetter = number.toFloat();
	}

//	MMcomm.SendMessage("G: " + (String)_G);
//	MMcomm.SendMessage("X: " + (String)_X + "Y: " + (String)_Y);
//	MMcomm.SendMessage("Xpoz: " + (String)_XPosition + "Ypoz: " + (String)_YPosition);
}