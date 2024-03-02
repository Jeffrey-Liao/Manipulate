#pragma once
#pragma once
#ifndef UI_H
#define UI_H
#include "cmd.h"
class UiDock
{
	string Ui_Dock;
public:
	static UiDock ui_dock;
	UiDock();
	UiDock(string message);
	void change(string);
	void call();
	UiDock& operator<<(string message);
	void operator<<(JUi* message);
};
class JUi
{

protected:
	bool switchLine;
	string UI_Message;
	static void charClear()
	{
		cout << "\b \b";
	}
	static void moveBack(int byteSize = 1)
	{
		for (int n = 0; n < byteSize; ++n)
			cout << "\b";
	}
	static void lineClear(int byteSize = 1)
	{
		for (int n = 0; n < byteSize; ++n)
			charClear();
	}
	static void drawEmpty(int byteSize)
	{
		for (int n = 0; n < byteSize; ++n)
			cout << " ";
		moveBack(byteSize);
	}
	JUi();
	JUi(string newMessage);
	void clear();
	virtual void change(string newMessage) =0;
public:
	void call();
};
UiDock UiDock::ui_dock;
class UiHint :public JUi
{
public:
	static UiHint ui_hint;
	UiHint();
	UiHint(string message);
	virtual void change(string);
	void operator<<(string message);
};
UiHint UiHint::ui_hint;
class UiMessage :public JUi
{
public:
	bool isErrorMessage;
	static UiMessage ui_message;
public:
	UiMessage();
	UiMessage(bool error);
	UiMessage(string newMessage);
	UiMessage(string newMessage, bool error);
	void change(string);
	virtual UiMessage& operator<< (string message);
};
UiMessage UiMessage::ui_message;
#endif