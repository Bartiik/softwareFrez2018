#pragma once
#include "Arduino.h"
class Communication
{
private:
	String _message;
	bool _newMessage;
public:
	Communication();
	~Communication();
	void SendMessage(String);
	void ReceiveMessage(String);
	String LatestMessage();
	void SendReply();
	bool IsMessageNew();

};

extern Communication MMcomm