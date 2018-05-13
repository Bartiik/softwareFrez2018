#pragma once
#include <stdint.h>
#include <Arduino.h>
#include "Communication.h"
class MMStateMachine
{
private:
	uint8_t _state;
	bool _Endstop;
	uint8_t StateChangeLookupTable[3][4] = {
	{IDLE_STATE, ERROR_STATE, ERROR_STATE, ERROR_STATE},
	{ERROR_STATE, ERROR_STATE, ERROR_STATE, ERROR_STATE},
	{IDLE_STATE, IDLE_STATE, IDLE_STATE, IDLE_STATE}};
	
public:

	MMStateMachine();
	~MMStateMachine();
	void MMSafetyBegin(uint16_t ); // all pins setup
	uint8_t CurrentState(); // return current state
	bool TryUpdateState(String ); // try to use the command to update state, returns true if the command is unused, false if is
	void SetErrorState();
	void CheckEndstops();
	bool IsEndstopPressed();
	void Reset();
};

extern MMStateMachine StateMachine;