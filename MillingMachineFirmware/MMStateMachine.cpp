#include "MMStateMachine.h"
#include "GCodeInterpreter.h"
#include "config.h"

MMStateMachine StateMachine;

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
	bool commandIsUsed = true;
	uint8_t cmd;
	if (command == COMMUNICATION_TEST_COMMAND) cmd = 0;
	else if (command == ERROR_COMMAND) cmd = 1;
	else if (command == RESET_COMMAND) cmd = 2;
	else
	{
		_state = EXECUTION_STATE;
		commandIsUsed = false;
	}
	if (commandIsUsed)
	{
		_state = StateChangeLookupTable[_state][cmd];
	}
	MMcomm.SendMessage(command);
	return commandIsUsed;
}

void MMStateMachine::Reset()
{
	_state = INIT_STATE;
}