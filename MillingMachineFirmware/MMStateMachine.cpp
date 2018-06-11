#include "MMStateMachine.h"
#include "GCodeInterpreter.h"
#include "config.h"
#include "SMotor.h"

MMStateMachine StateMachine;

MMStateMachine::MMStateMachine()
{
	_EndstopEn = 1;
	_state = INIT_STATE;
	for (int i = 0; i < NO_OF_ENDSTOPS; i++)
	{
		_endstopArray[i] = false;
	}
}
MMStateMachine::~MMStateMachine() {}

/* autor: Bartek Kudroń
	Inicjalizacja klasy bezpieczeństwa. Działąnie niesprawdzone.
*/
void MMStateMachine::MMSafetyBegin()
{
	pinMode(X_MIN_ENDSTOP_PIN, INPUT_PULLUP);
	pinMode(X_MAX_ENDSTOP_PIN, INPUT_PULLUP);
	pinMode(Y_MIN_ENDSTOP_PIN, INPUT_PULLUP);
	pinMode(Y_MAX_ENDSTOP_PIN, INPUT_PULLUP);
	pinMode(Z_MIN_ENDSTOP_PIN, INPUT_PULLUP);
	pinMode(Z_MAX_ENDSTOP_PIN, INPUT_PULLUP);
	pinMode(TABLE_FLIP_ENDSTOP_1, INPUT_PULLUP);
	pinMode(TABLE_FLIP_ENDSTOP_2, INPUT_PULLUP);
	pinMode(TABLE_HOLD_LEFT_ENDSTOP_1, INPUT_PULLUP);
	pinMode(TABLE_HOLD_LEFT_ENDSTOP_2, INPUT_PULLUP);
	pinMode(TABLE_HOLD_LEFT_ENDSTOP_3, INPUT_PULLUP);
	pinMode(TABLE_HOLD_LEFT_ENDSTOP_4, INPUT_PULLUP);
	pinMode(TABLE_HOLD_RIGHT_ENDSTOP_1, INPUT_PULLUP);
	pinMode(TABLE_HOLD_RIGHT_ENDSTOP_2, INPUT_PULLUP);
	pinMode(TABLE_HOLD_RIGHT_ENDSTOP_3, INPUT_PULLUP);
	pinMode(TABLE_HOLD_RIGHT_ENDSTOP_4, INPUT_PULLUP);
	pinMode(TABLE_HOLD_MAX_ENDSTOP, INPUT_PULLUP);
	pinMode(TABLE_LEVEL_ENDSTOP, INPUT_PULLUP);
	pinMode(TABLE_LEVEL_PROBE, INPUT_PULLUP);
}
/* autor: Bartek Kudroń
	zwraca stan maszyny.
*/
uint8_t MMStateMachine::CurrentState()
{
	return _state;
}


void MMStateMachine::SetEndstopsEn(bool EN) {
	_EndstopEn = EN;
}



/* autor: Bartek Kudroń
	funkcja sprawdza krańcówki i zapisuje do macierzy oraz zmienia enable konkretnych napędów.
*/
void MMStateMachine::ResolveEndstops()
{


		bool tempArray[NO_OF_ENDSTOPS] = {
			digitalRead(X_MIN_ENDSTOP_PIN),				digitalRead(X_MAX_ENDSTOP_PIN),
			digitalRead(Y_MIN_ENDSTOP_PIN),				digitalRead(Y_MAX_ENDSTOP_PIN),
			digitalRead(Z_MIN_ENDSTOP_PIN),				digitalRead(Z_MAX_ENDSTOP_PIN),
			digitalRead(TABLE_FLIP_ENDSTOP_1),			digitalRead(TABLE_FLIP_ENDSTOP_2),
			digitalRead(TABLE_HOLD_LEFT_ENDSTOP_1),		digitalRead(TABLE_HOLD_LEFT_ENDSTOP_2),
			digitalRead(TABLE_HOLD_LEFT_ENDSTOP_3),		digitalRead(TABLE_HOLD_LEFT_ENDSTOP_4),
			digitalRead(TABLE_HOLD_RIGHT_ENDSTOP_1),	digitalRead(TABLE_HOLD_RIGHT_ENDSTOP_2),
			digitalRead(TABLE_HOLD_RIGHT_ENDSTOP_3),	digitalRead(TABLE_HOLD_RIGHT_ENDSTOP_4),
			digitalRead(TABLE_HOLD_MAX_ENDSTOP),		digitalRead(TABLE_LEVEL_ENDSTOP),
			!digitalRead(TABLE_LEVEL_PROBE)  };

		for (int i = 0; i < NO_OF_ENDSTOPS; i++)
		{
			_endstopArray[i] = tempArray[i];
		}


	if (_EndstopEn) {
		if (_endstopArray[0] + _endstopArray[1])
		{
			XStepper.SetEnable(true);
		}

		if (_endstopArray[2] + _endstopArray[3])
		{
			YStepper.SetEnable(true);
		}

		if (_endstopArray[4] + _endstopArray[5] + _endstopArray[17] + _endstopArray[18])
		{
			ZStepper.SetEnable(true);
		}
	}
	/*
	if((_endstopArray[8] + _endstopArray[9] + _endstopArray[10] + _endstopArray[11])*(_endstopArray[12] + _endstopArray[13] + _endstopArray[14] + _endstopArray[15]) + _endstopArray[16])
	{
		Table.SetEnable(false);
	}
	if((_endstopArray[6] + _endstopArray[7])
	{
		FlipTable.SetEnable(false);
	}
	*/

}

/*
	Autor: Bartosz Kudroń
	funkcja zwraca wartość danej krańcówki, według wartości:
	0 - X-Min 1 - X-Max	2 - Y-Min 3 - Y-Max
	4 - Z-Min 5 - Z-Max	6 - endstop obrotu stołu I
	7 - endstop obrotu stołu II
	8-11 - kolejne endstopy zaciskania z lewej strony
	12-15 - kolejne endstopy zaciskania z prawej strony
	16 - endstop maksymalnego rozłożenia zaciskania stołu
	17 - endstop zerowania stołu
	18 - czujnik zetknięcia wrzeciona ze stołem
	19 - próbnik działania stycznika wrzeciona
*/

bool MMStateMachine::returnEndstop(uint8_t nr)
{
	return _endstopArray[nr];
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
	else if (command == STANDARD_REPLY_COMMAND) cmd = 3;
	else
	{
		commandIsUsed = false;
	}
	if (commandIsUsed)
	{
		_state = StateChangeLookupTable[cmd][_state];
		if (_state == ERROR_STATE)
			MMcomm.SendMessage(UNEXPECTED_STATE_ERROR);
		else
			MMcomm.SendReply();
	}
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
void MMStateMachine::SetErrorState(String error)
{
	MMcomm.SendMessage(error);
	_state = ERROR_STATE;
}
void MMStateMachine::SetErrorState()
{
	MMcomm.SendMessage(UNKNOWN_ERROR);
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
