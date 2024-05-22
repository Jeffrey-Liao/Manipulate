#pragma once
#pragma once
#ifndef UI_H
#define UI_H
#include "debugInfor.h"
class UiDock
{
	string Ui_Dock;
	bool show;
public:
	static UiDock ui_dock;
	UiDock();
	void change(string);
	void call();
	inline bool isEmpty()
	{
		return Ui_Dock.empty();
	}
	UiDock& operator<<(string message);
};
class JUi
{
protected:
	bool existDock;
	string UI_Message;
	JUi();
public:
	static void charClear()
	{
		cout << "\b \b";
	}
	static void moveBack(int byteSize = 1)
	{
		for (int n = 0; n < byteSize; ++n)
			cout << "\b";
	}
	static void strClear(int byteSize = 1)
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
	static void borderLine(int byteSize)
	{
		for (int n = 0; n < byteSize; ++n)
			cout << "-";
	}
	static bool confirm(string message)
	{
		cout << "\n";
		borderLine(message.size() + 55);
		cout << "\n";
		cout << message << "(Press Enter or 'Y' for yes, press other key for deny.)";
		cout << "\n";
		borderLine(message.size() + 55);
		char result = _getch();
		cout << "\n";
		if (result == 'y' || result == 'Y' || result == ENTER)
			return true;
		else
			return false;
	}
	void end();
	void messageClear();
	void clear();
	void dock();
	void call();
	bool isEmpty();
	bool existMessage();
};
class UiHint :public JUi
{
public:
	UiHint();
	void change(string); 
	void clear();
	void call();
	UiHint& operator<<(string message);
};
class UiMessage :public JUi
{
public:
	UiMessage();
	void change(string);
	void change(string,bool);
	void remove(int charSize = 1);
	UiMessage& operator<< (string message);
	UiMessage& operator[](bool line);
};
static UiHint ui_hint;
static UiMessage ui_message;
class UiNoticeMessage:public JUi
{
	bool isErrorMessage;
public:
	UiNoticeMessage();
	void change(string);
	void call();
	void error();
	UiNoticeMessage& operator[](bool error);
	UiNoticeMessage& operator<<(string message);
};
static UiNoticeMessage ui_notice;
static class UiCharMessage :public JUi
{
public:
	UiCharMessage();
	static UiCharMessage ui_char;
	void showChar(char newChar);
	void remove();
	int getIndex();
	void clear();
	UiCharMessage& operator<<(string newKey);
	UiCharMessage& operator<<(char newKey);
}ui_char;
static class UiLoading :public JUi
{
	bool change = true;
	float maximum = 0;
	int getIndex(int percentage)
	{
		int index = percentage / 10;
		return index * 2 + 1;
	}
public:
	 UiLoading& operator[](float maximum)
	{
		this->maximum = maximum;
		return *this;
	}
	 void complete()
	 {
		 UI_Message = "[> > > > > > > > > >]100%";
		 this->call();
	 }
	 void call()
	 {
		 cout << this->UI_Message;
	 }
	 void operator<<(float current)
	 {
		 if (maximum > 0)
		 {
			 int percentage = current / maximum * 100;
			 if (percentage == 0)
			 {
				 UI_Message = "[- - - - - - - - - -]" + to_string(percentage) + '%';
			 }
			 else if (percentage == 100)
			 {
				 this->complete();
			 }
			 else
			 {
				 int index = this->getIndex(percentage);
				 change = UI_Message[index] != '>' || current == maximum;
				 if (current != maximum&& change)
					 UI_Message[index] = '>';
				 for (int n = UI_Message.size() - 1; UI_Message[n] == '%' || UI_Message[n] <= '9' && UI_Message[n] >= '0'; --n)
				 {
					 UI_Message.erase(n);
				 }
				 UI_Message += to_string(percentage) + '%';
			 }
			 if (change)
			 {
				 this->call();
				 JUi::moveBack(UI_Message.size());
				 change = false;
			 }
			 
		 }
		 if (current == maximum)
		 {
			 maximum = 0;
			 UI_Message.clear();
		 }
	 }
}ui_loading;
static onebyte curStage= UNIVER_CMD;
#endif