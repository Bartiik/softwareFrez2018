#include "config.h"
#include "MMStateMachine.h"
#include "Communication.h"

boolean stringComplete = false;
bool val = true;
void setup()
{
	cli(); //Timer 0 - endstops
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0 = 0;
	OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0A);
	sei();


	Serial.begin(BAUD_RATE);
	pinMode(LED_PIN, OUTPUT);
	StateMachine.MMSafetyBegin(N_C);
}

ISR(TIMER0_COMPA_vect) //check endstops, if any is pressed
{
	StateMachine.CheckEndstops();
}

void loop()
{

	switch (StateMachine.CurrentState())
	// nothing should happen outside this switch
	{
	case INIT_STATE:
	{
		// BEGIN OF INIT STATE

		// END OF INIT STATE
	}
	break;
	case IDLE_STATE:
	{
		// BEGIN OF IDLE STATE

		// END OF IDLE STATE
	}
	break;
	case COMMAND_STATE:
	{
		// BEGIN OF COMMAND STATE

		// END OF COMMAND STATE
	}
	break;
	case ERROR_STATE:
	{
		// BEGIN OF ERROR STATE

		// END OF ERROR STATE
	}
	break;
	default:
	{
		// COMPLETE FUCKUP STATE, IF HAPPENS THE PROGRAM
		// IS SOMEWHERE COMPLETELY FUCKED UP
	}

	};
}

void serialEvent() {
	String inputString = "";
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		inputString += inChar;
		if (inChar == '\n') {
			StateMachine.TryUpdateState(inputString);
			MMcomm.ReceiveMessage(inputString);
		}
	}
}

