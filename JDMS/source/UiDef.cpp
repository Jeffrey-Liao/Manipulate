#include"JUi.h"
#define CONTINUE "(press any key to continue)"
#pragma region JUIDEF
JUi::JUi()
	:existDock(false)
{
}
bool JUi::isEmpty()
{
	return this->UI_Message.empty();
}
void JUi::call()
{
	cout << UI_Message;
}
void JUi::dock()
{
	if(!existDock)
		UiDock::ui_dock.call(), existDock = true;
}
void JUi::end()
{
	cout << "\n";
	existDock = false;
	this->clear();
}
void JUi::messageClear()
{
	this->UI_Message.clear();
}
void JUi::clear()
{
	strClear(UI_Message.size());
	this->UI_Message.clear();
}
#pragma endregion
#pragma region DOCKDEF
UiDock::UiDock()
{}
void UiDock::change(string newMessage)
{
	this->Ui_Dock = newMessage + "::";
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
#pragma endregion
#pragma region HINTDEF
UiHint::UiHint()
	:JUi()
{
}
void UiHint::change(string newMessage)
{
	this->UI_Message = '-' + newMessage;
}
UiHint& UiHint::operator<<(string message)
{
	change(message);
	this->drawEmpty(20);
	this->call();
	return *this;
}
void UiHint::call()
{
	if (this->UI_Message.size() > 1)
	{
		cout << this->UI_Message;
		moveBack(UI_Message.size());
	}
}
#pragma endregion
#pragma region MESSAGEDEF
UiMessage::UiMessage()
	:JUi()
{}
void UiMessage::change(string message)
{
	this->UI_Message = message;
}
void UiMessage::change(string newMessage, bool lineSwitch)
{
	this->UI_Message = newMessage;
}
void UiMessage::remove(int charSize)
{
	if (this->UI_Message.size() > 0)
	{
		for (int n = 0; n < charSize; ++n)
			this->UI_Message.erase(this->UI_Message.size() - 1);
		this->strClear(charSize);
	}
	else
		throw new LiaoException("UiMessage", "remove", "remove element from empty message");
}
UiMessage& UiMessage::operator[](bool showDock)
{

	if (!existDock&&showDock)
		dock(),existDock = showDock;
	return *this;
}
UiMessage& UiMessage::operator<< (string message)
{
	this->change(message);
	this->call();
	return *this;
}
#pragma endregion
#pragma region NOTICEDEF
UiNoticeMessage::UiNoticeMessage()
	:JUi(), isErrorMessage(false)
{}
void UiNoticeMessage::change(string newMessage)
{
	if (isErrorMessage)
		this->UI_Message = "\n!<" + newMessage + ">!";
	else
		this->UI_Message = ">" + newMessage + "<" + CONTINUE;
}
void UiNoticeMessage::call()
{
	cout << UI_Message;
	if (!isErrorMessage)
	{
		_getch();
		strClear(this->UI_Message.size());
	}
	else
		end();
	this->UI_Message.clear();
}UiNoticeMessage& UiNoticeMessage::operator[](bool newError)
{
	this->isErrorMessage = newError;
	return *this;
}
UiNoticeMessage& UiNoticeMessage::operator<<(string message)
{
	this->change(message);
	this->call();
	return *this;
}
void UiNoticeMessage::error()
{
	this->isErrorMessage = !this->isErrorMessage;
}
#pragma endregion
#pragma region CHARDEF
UiCharMessage::UiCharMessage()
	:JUi()
{}
void UiCharMessage::showChar(char newChar)
{
	cout << newChar;
	this->UI_Message += newChar;
}
void UiCharMessage::remove()
{
	if (this->UI_Message.size() > 0)
	{
		this->UI_Message.erase(this->UI_Message.size() - 1);
		charClear();
	}
	else
		throw new LiaoException("UiCharMessage", "remove", "remove element from empty message");
}
void UiCharMessage::clear()
{
	this->UI_Message.clear();
}
int UiCharMessage::getIndex()
{
	if (!this->UI_Message.empty())
		return this->UI_Message.size() - 1;
	else
		throw new LiaoException("UiCharMessage", "getIndex", "get index from empty message");
}
UiCharMessage& UiCharMessage::operator<<(string newKey)
{
	this->UI_Message = newKey;
	return *this;
}
#pragma endregion
UiCharMessage& UiCharMessage::operator<<(char newKey)
{
	this->showChar(newKey);
	return *this;
}
UiHint UiHint::ui_hint;
UiDock UiDock::ui_dock;
UiNoticeMessage UiNoticeMessage::ui_notice;
UiCharMessage UiCharMessage::ui_char;