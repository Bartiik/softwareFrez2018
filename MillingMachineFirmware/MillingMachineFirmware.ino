#include "config.h"
//#include "MMStateMachine.h"
#include "GCodeInterpreter.h"
#include "Communication.h"

String inputString = "";
boolean stringComplete = false;
bool initial = true;

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
		ProcessNewMessage();
		// END OF INIT STATE
	}
	break;
	case IDLE_STATE:
	{
		// BEGIN OF IDLE STATE
		ProcessNewMessage();
		// END OF IDLE STATE
	}
	break;

	case EXECUTION_STATE:
	{
		ProcessNewMessage();
		Command.ExecuteStep();
		// BEGIN OF COMMAND EXECUTION STATE - PERFORM COMMAND

		// END OF COMMAND STATE
	}
	break;

	case ERROR_STATE:
	{
		// BEGIN OF ERROR STATE
		ProcessNewMessage();
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
		
		if (inChar == '\n') {
			stringComplete = true;
		}
		else if(inChar - '0' > 0)
		{
			inputString += inChar;
		}
	}
}
bool ProcessNewMessage()
{
	if (stringComplete)
	{
		if (!StateMachine.TryUpdateState(inputString))
			MMcomm.ReceiveMessage(inputString);
		inputString = "";
		stringComplete = false;
		return true;
		
	}
	else return false;
}

