#include "config.h"


String inputString = "";
boolean stringComplete = false;
bool val = true;
int millingMachineState = INIT_STATE;
void setup()
{
	Serial.begin(BAUD_RATE);
	pinMode(LED_PIN, OUTPUT);
}

void loop()
{

	switch (millingMachineState)
	// nothing should happen outside this switch
	{
	case INIT_STATE:
	{
		// BEGIN OF INIT STATE
		if (stringComplete)
		{
			stringComplete = false;
			if (inputString == "M0")
			{

				millingMachineState = IDLE_STATE;
			}
				
			inputString = "";
		}





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
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		inputString += inChar;
		if (inChar == '\n') {
			stringComplete = true;
		}
	}
}
void sendMessage()
{

}