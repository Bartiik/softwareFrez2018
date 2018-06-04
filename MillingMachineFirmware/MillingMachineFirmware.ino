#include <Servo.h>
#include "config.h"
//#include "MMStateMachine.h"
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

/* 
ZASADA DZIAŁANIA PROGAMU (IDEA, NIEZWERYFIKOWANA - MOGĄ BYĆ BŁĘDY) 

kod opiera się na reagowaniu na konkretne komendy. W pliku MMStateMachine.h znajdują się opisy komend. Komendy U to są moje własne, M i G to komendy standardowe.
na podstawie kilku komend U w pliku MMStateMachine.cpp dochodzi do zmian stanu maszyny między INIT, IDLE, EXECUTE, ERROR.

W LOOP znajduje się switch stanów. Jak na razie każdy jedynie co robi, to interpretuje komendy otrzymane.
Jeżeli otrzymana komenda należy do listy kilku wybranych komend U, to od razu jest wykonywana, jeśli nie, to zostaje wysłana do klasy Communication, gdzie jest przechowywana na potrzeby dalszego wykorzystania.
W pliku GCodeInterpreter.cpp znajduje się interpretacja G-Code'ów, nie są jeszcze zaimplementowane żadne jej użycia.
Koncepcja programu jest taka, że w stanie IDLE sprawdzana jest komenda, jeśli zgadza się z istniejącymi, 
to wykonać ma się funkcja PrepareForExecution(), w której powinny znajdować się podstawowe obliczenia wstępne, wykonywane tylko raz.
Następnie stan maszyny ma się zmienić na EXECUTION, i w tym stanie ma się znajdować funkcja ExecuteStep(), która wykonywać ma się do momentu zakończenia komendy i wysłania wiadomości zwrotnej do frezarki.
Potem nastąpić ma powrót do IDLE, gdzie czekać ma program na nową komendę.

WAŻNE - program windowsowy do komunikacji przetwarza komendy przed wysłaniem, nie przyjmie nic, co nie zgadza się z regexem konkretnym - wszystko musi składać się z jednej z 10 liter i następnie liczby.
Pary litery z liczbą można łączyć w jeden łańcuch, np. X10Y20Z30, wtedy wyśle się wszystko naraz.
Litery przyjmowane przez komunikator - "GXYZIJMSFU". Wielkość nieważna.
 
Polecam poczytać działanie klas, powinno być w miarę proste i niezbyt skomplikowane ;)
*/


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

	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = RPS2_5;
	TCCR1B |= (1 << CS11);
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
	StateMachine.CheckEndstops();
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
		StateMachine.ResolveEndstops();
		for (int i = 0; i < 20; i++) {
			Serial.print((String)StateMachine.returnEndstop(i) + " ");
		}
		Serial.println(" ");
	
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
	
		StateMachine.ResolveEndstops();


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
		// BEGIN OF ERROR STATE
		// END OF ERROR STATE
	}
	break;
	default:
	{

		// COMPLETE FUCKUP STATE, IF HAPPENS THE PROGRAM
		// IS SOMEWHERE COMPLETELY FUCKED UP
		StateMachine.SetErrorState(UNHANDLED_STATE_ERROR);
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

void debugLED()
{
	digitalWrite(13, var);
	var = !var;
}