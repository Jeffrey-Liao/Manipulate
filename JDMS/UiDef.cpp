#include"JUi.h"
JUi::JUi()
	:switchLine(false)
{
}
JUi::JUi(string newMessage)
{
	this->UI_Message = newMessage;
}
void JUi::call()
{
	cout << UI_Message;
}
void JUi::clear()
{
	lineClear(UI_Message.size());
	this->UI_Message.clear();
}

UiDock::UiDock()
{}
UiDock::UiDock(string message)
	:Ui_Dock(message+"::")
{}
void UiDock::change(string newMessage)
{
	this->Ui_Dock = newMessage+"::";
}
void UiDock::call()
{
	cout << this->Ui_Dock;
}
UiDock& UiDock::operator<<(string message)
{
	this->change(message);
	this->call();
	return *this;
}
void UiDock::operator<<(JUi* message)
{
	cout << Ui_Dock;
	message->call();
}
UiHint::UiHint()
	:JUi()
{
}
UiHint::UiHint(string message)
	:JUi(message)
{
}
void UiHint::change(string newMessage)
{
	this->UI_Message = '-'+newMessage ;
}
void UiHint::operator<<(string message)
{
	change(message);
	this->call();
}
UiMessage::UiMessage()
	:isErrorMessage(false),JUi()
{}
UiMessage::UiMessage(bool error)
	:isErrorMessage(error),JUi()
{}
UiMessage::UiMessage(string newMessage)
	:isErrorMessage(false),JUi(newMessage)
{}
UiMessage::UiMessage(string newMessage, bool error)
	:isErrorMessage(error), JUi(newMessage)
{}
void UiMessage::change(string message)
{
	if (isErrorMessage)
		this->UI_Message = "<" + message + ">";
	else
		this->UI_Message
}