#pragma once
#include <stdint.h>
#include <Arduino.h>
class MMStateMachine
{
private:
	uint8_t _state;
	bool _Endstop;
public:

	MMStateMachine();
	~MMStateMachine();
	void MMSafetyBegin(uint16_t ); // all pins setup
	uint8_t CurrentState(); // return current state
	bool TryUpdateState(String ); // try to use the command to update state, returns true if the command is unused, false if is
	void SetErrorState();
	void CheckEndstops();
	bool IsEndstopPressed();
};

extern MMStateMachine StateMachine;