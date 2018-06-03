#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "Communication.h"



class MMStateMachine
{
private:
	uint8_t _state;
	bool _Endstop;
	
	uint8_t StateChangeLookupTable[4][4] = {
	{IDLE_STATE, ERROR_STATE, ERROR_STATE, ERROR_STATE},
	{ ERROR_STATE, ERROR_STATE, ERROR_STATE, ERROR_STATE},
	{ INIT_STATE, INIT_STATE, INIT_STATE, INIT_STATE },
	{ INIT_STATE, IDLE_STATE,EXECUTION_STATE,ERROR_STATE} };

	bool _endstopArray[NO_OF_ENDSTOPS];
	
public:
	MMStateMachine();
	~MMStateMachine();
	void MMSafetyBegin(); // all pins setup
	uint8_t CurrentState(); // return current state
	bool TryUpdateState(String ); // try to use the command to update state, returns true if the command is unused, false if is
	void SetErrorState(String);
	void SetErrorState();
	void SetExecutionState();
	void SetIdleState();
	void Reset();
	void CheckEndstops();
	void ResolveEndstops();
	bool returnEndstop(uint8_t);
};

extern MMStateMachine StateMachine;
