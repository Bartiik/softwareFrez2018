#include "GCodeInterpreter.h"


GCodeInterpreter::GCodeInterpreter()
{
	Clear();
}

GCodeInterpreter::~GCodeInterpreter(){}

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

void GCodeInterpreter::ExecuteStep()
{
	switch ((int)_G)
	{
	case 0: //G0 command - to be filled

		break;
	}
}

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