#include "MMStateMachine.h"
#include "GCodeInterpreter.h"
#include "config.h"

MMStateMachine StateMachine;

MMStateMachine::MMStateMachine()
{
	_state = INIT_STATE;
}
MMStateMachine::~MMStateMachine(){}

/* autor: Bartek Kudroń
	Inicjalizacja klasy bezpieczeństwa. Działąnie niesprawdzone.
*/
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
/* autor: Bartek Kudroń
	zwraca stan maszyny.
*/
uint8_t MMStateMachine::CurrentState()
{
	return _state;
}
/* autor: Bartek Kudroń
	sprawdzenie krańcówek, czy któraś nie jest wciśnięta. niesprawdzone
*/
void MMStateMachine::CheckEndstops()
{
	_Endstop = digitalRead(X_MIN_ENDSTOP_PIN) + digitalRead(X_MAX_ENDSTOP_PIN) + digitalRead(Y_MIN_ENDSTOP_PIN) + digitalRead(Y_MAX_ENDSTOP_PIN) + digitalRead(Z_MIN_ENDSTOP_PIN) + digitalRead(Z_MAX_ENDSTOP_PIN) > 0 ? true : false;
}
/* autor: Bartek Kudroń
	zwraca czy wciśnięta jest krańcówka.
*/
bool MMStateMachine::IsEndstopPressed()
{
	return _Endstop;
}
/* autor: Bartek Kudroń
	próba wykorzystania komendy do zmiany stanu (sprawdzenie czy komenda należy do jednej z konkretnych komend U i zmiana jeśli tak).
*/
bool MMStateMachine::TryUpdateState(String command)
{
	bool commandIsUsed = true;
	uint8_t cmd;
	if (command == COMMUNICATION_TEST_COMMAND) cmd = 0;
	else if (command == ERROR_COMMAND) cmd = 1;
	else if (command == RESET_COMMAND) cmd = 2;
	else
	{
		commandIsUsed = false;
	}
	if (commandIsUsed)
	{
		_state = StateChangeLookupTable[_state][cmd];
	}
	MMcomm.SendMessage(command);
	return commandIsUsed;
}
/* autor: Bartek Kudroń
	zmiana stanu na INIT
*/
void MMStateMachine::Reset()
{
	_state = INIT_STATE;
}
/* autor: Bartek Kudroń
zmiana stanu na error.
*/
void MMStateMachine::SetErrorState()
{
	_state = ERROR_STATE;
}
/* autor: Maciej Wiecheć
zmiana stanu na execution.
*/
void MMStateMachine::SetExecutionState()
{
	_state = EXECUTION_STATE;
}
/* autor: Maciej Wiecheć
zmiana stanu na idle.
*/
void MMStateMachine::SetIdleState()
{
	_state = IDLE_STATE;
}
