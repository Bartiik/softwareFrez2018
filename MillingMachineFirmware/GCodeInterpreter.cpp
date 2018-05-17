#include "GCodeInterpreter.h"
#include "Communication.h"
#include "MMStateMachine.h"
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
	_X = DUMMY_VALUE;
	_Y = DUMMY_VALUE;
	_Z = DUMMY_VALUE;
	_I = DUMMY_VALUE;
	_J = DUMMY_VALUE;
	_S = DUMMY_VALUE;
	_F = DUMMY_VALUE;
}
/* autor: Bartek Kudroń
funkcja wykonywana co krok programu, w zależności od komendy różny kod.
*/
void GCodeInterpreter::ExecuteStep()
{
	if (newCommand)
	{
		PrepareForExecution();
		newCommand = false;
	}
	//			G COMMANDS

	switch ((int)_G)
	{
	case 0: //G00 command - to be filled

		break;
	case 1: //G01 command - to be filled

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
!!! NIESPRAWDZONA !!!
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
			if (((int)command[i] - '0' >= 0 && (int)command[i] - '0' <= 9) || command[i] == '.')
				number += command[i];
			break;
		}
	}
	if (number != "")
	{
		*currentLetter = number.toFloat();
	}
}