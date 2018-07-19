
#include <Servo.h>
#include "config.h"
#include "MMStateMachine.h"
#include "GCodeInterpreter.h"
#include "Communication.h"
#include "SMotor.h"
#include "RoTable.h"
#include "BLDCDriver.h"


String inputString = "";
boolean stringComplete = false;
bool initial = true;
bool var = false;
bool ExecutionInterrupt = false;

void setup()
{
	pinMode(D9_ENABLE_PIN, OUTPUT);
	digitalWrite(D9_ENABLE_PIN, HIGH);
	cli(); //Timer 0 - endstops - 1000Hz
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0 = 0;
	OCR0A = 249;// = (16*10^6) / (200*64) - 1 (must be <256)
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0A);

	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = RPS2_5;
	TCCR1B |= (1 << CS10);
	TIMSK1 |= (1 << TOIE1);

	sei();


	Serial.begin(BAUD_RATE);
	pinMode(LED_PIN, OUTPUT);
	StateMachine.MMSafetyBegin();
	spindle.init();
	Table.init();
	XStepper.Init(X_DIR_PIN, X_STEP_PIN, X_ENABLE_PIN);
	YStepper.Init(Y_DIR_PIN, Y_STEP_PIN, Y_ENABLE_PIN);
	ZStepper.Init(Z_DIR_PIN, Z_STEP_PIN, Z_ENABLE_PIN);

}

ISR(TIMER1_OVF_vect) { //timer for steppers
	 //by changing this value we can change the speed of rotation
	if (StateMachine.CurrentState() == EXECUTION_STATE) {
		ExecutionInterrupt = true;
	}
	//TCNT1 = 1000;
	//Serial.print(millis());
	//Serial.print("   ");
	//Serial.println(micros());
	
}


ISR(TIMER0_COMPA_vect) //check endstops, if any is pressed
{
	StateMachine.ResolveEndstops();
	Command.time++;
}

void loop()
{

	
	//StateMachine.ResolveEndstops();
	ProcessNewMessage();
	//if (XStepper.GetBoolEnable()) MMcomm.SendMessage("EN=1");
	//else MMcomm.SendMessage("En=0");
	switch (StateMachine.CurrentState())
	// nothing should happen outside this switch
	{
	case INIT_STATE:
	{
		/*for (int i = 0; i < 19; i++) {
			Serial.print((String)StateMachine.returnEndstop(i) + " ");
		}
		Serial.println(" ");*/
	
		// BEGIN OF INIT STATE

		// END OF INIT STATE
	}
	break;
	case IDLE_STATE:
	{

		// BEGIN OF IDLE STATE
		if (MMcomm.MessageIsNew())
		{
			if (Command.Interpret(MMcomm.LatestMessage())) {


				Command.PrepareForExecution();
				if (StateMachine.CurrentState() == IDLE_STATE) {

					StateMachine.SetExecutionState();
				}
			}
			
		}
		// END OF IDLE STATE
	}
	break;

	case EXECUTION_STATE:
	{
	
		if (ExecutionInterrupt)
		{
			Command.ExecuteStep();
			ExecutionInterrupt = false;
		}
	
		// END OF COMMAND STATE
	}
	break;

	case ERROR_STATE:
	{
		Table.stop();
		Command.SetSteppersEn(1);
		spindle.setSpeed(1000);
		MMcomm.SendReply();
		// BEGIN OF ERROR STATE
		// END OF ERROR STATE
	}
	break;
	default:
	{

		// COMPLETE FUCKUP STATE, IF HAPPENS THE PROGRAM
		// IS SOMEWHERE COMPLETELY FUCKED UP
		StateMachine.SetErrorState(UNHANDLED_STATE_ERROR);
		Table.stop();
		StateMachine.Reset();
	}

	};
}

void serialEvent() {
	

	
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		
		if (inChar == '\n') {
			stringComplete = true;
		}
		else if(inChar  >= 33)
		{
			inputString += inChar; 
		}
	}
}
bool ProcessNewMessage()
{
	if (stringComplete)
	{
		stringComplete = false;
		if (!StateMachine.TryUpdateState(inputString))
			MMcomm.ReceiveMessage(inputString);
		inputString = "";
		return true;
	}
	else return false;
}