#include "config.h"
//#include "MMStateMachine.h"
#include "GCodeInterpreter.h"
#include "Communication.h"

String inputString;
boolean stringComplete = false;
bool initial = true;
void setup()
{
	cli(); //Timer 0 - endstops - 1000Hz
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0 = 0;
	OCR0A = 249;// = (16*10^6) / (200*64) - 1 (must be <256)
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

	case EXECUTION_STATE:
	{
		Command.ExecuteStep();
		// BEGIN OF COMMAND EXECUTION STATE - PERFORM COMMAND

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
		MMcomm.SendMessage("CRITICAL ERROR! UNKNOWN STATE. COMMUNICATION RESET REQUIRED");
		StateMachine.Reset();
	}

	};
}

void serialEvent() {
	
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		inputString += inChar;
		if (inChar == '\n') {

			if(!StateMachine.TryUpdateState(inputString))
				MMcomm.ReceiveMessage(inputString);
			inputString = "";

		}
	}
}

