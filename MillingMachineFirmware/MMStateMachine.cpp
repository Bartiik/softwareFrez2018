#include "MMStateMachine.h"
#include "config.h"
MMStateMachine::MMStateMachine()
{
	_state = INIT_STATE;
}
MMStateMachine::~MMStateMachine(){}

void MMStateMachine::MMSafetyBegin(uint16_t TableMaxEndstopPin)
{
	pinMode(X_MIN_ENDSTOP_PIN, INPUT);
	pinMode(X_MAX_ENDSTOP_PIN, INPUT);
	pinMode(Y_MIN_ENDSTOP_PIN, INPUT);
	pinMode(Y_MAX_ENDSTOP_PIN, INPUT);
	pinMode(Z_MIN_ENDSTOP_PIN, INPUT);
	pinMode(Z_MAX_ENDSTOP_PIN, INPUT);
	pinMode(TableMaxEndstopPin, INPUT);
}

uint8_t MMStateMachine::CurrentState()
{
	return _state;
}

void MMStateMachine::SetErrorState()
{
	_state = ERROR_STATE;
}

void MMStateMachine::CheckEndstops()
{
	_Endstop = digitalRead(X_MIN_ENDSTOP_PIN) + digitalRead(X_MAX_ENDSTOP_PIN) + digitalRead(Y_MIN_ENDSTOP_PIN) + digitalRead(Y_MAX_ENDSTOP_PIN) + digitalRead(Z_MIN_ENDSTOP_PIN) + digitalRead(Z_MAX_ENDSTOP_PIN) > 0 ? true : false;
}

bool MMStateMachine::IsEndstopPressed()
{
	return _Endstop;
}

bool MMStateMachine::TryUpdateState(String command)
{
	bool commandIsUsed = false;
	switch (_state)
	{
	case INIT_STATE:
	{
		if(command == COMMUNICATION_TEST_COMMAND)
		{
			_state = IDLE_STATE;
			commandIsUsed = true;
		}
	}
	break;
	case IDLE_STATE:
	{
		if (command == ERROR_COMMAND)
		{
			_state = ERROR_STATE;
			commandIsUsed = true;
		}

	}
	break;
	case COMMAND_STATE:
	{
		if (command == ERROR_COMMAND)
		{
			_state = ERROR_STATE;
			commandIsUsed = true;
		}
	}
	break;
	case ERROR_STATE:
	{
		if (command == RESET_COMMAND)
		{
			_state = IDLE_STATE;
			commandIsUsed = true;
		}
	}
	break;
	};
	return commandIsUsed;
}