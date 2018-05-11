#include "Communication.h"

Communication MMcomm;

Communication::Communication(){}
Communication::~Communication(){}

void Communication::SendMessage(String message )
{
	Serial.println(String(StateMachine.CurrentState()) + message);
}

void Communication::ReceiveMessage(String message)
{
	_message = message;
	_newMessage = true;
}

String Communication::LatestMessage()
{
	return _message;
	_newMessage = false;
}

bool Communication::MessageIsNew()
{
	return _newMessage;
}

void Communication::SendReply()
{
	SendMessage(STANDARD_REPLY_COMMAND);
}