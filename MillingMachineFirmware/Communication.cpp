#include "Communication.h"
#include "GCodeInterpreter.h"

Communication MMcomm;

Communication::Communication(){}
Communication::~Communication(){}

/* autor: Bartek Kudroń
	wysłanie wiadomości wraz ze stanem maszyny.
*/
void Communication::SendMessage(String message )
{

	Serial.println(String(StateMachine.CurrentState()) + message);
}
/* autor: Bartek Kudroń
	otrzymanie komendy i przechowanie jej
*/
void Communication::ReceiveMessage(String message)
{
	_message = message;
	_newMessage = true;
}
/* autor: Bartek Kudroń
	zwrot najnowszej komendy.
*/
String Communication::LatestMessage()
{
	_newMessage = false;
	return _message;
	
}
/* autor: Bartek Kudroń
	test czy wiadomość została użyta
*/
bool Communication::MessageIsNew()
{
	return _newMessage;
}
/* autor: Bartek Kudroń
	wysłanie odpowiedzi do kompa
*/
void Communication::SendReply()
{
	SendMessage(STANDARD_REPLY_COMMAND+Command.returnPosition());
}