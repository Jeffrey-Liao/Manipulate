#pragma once
#include "../InforUnit/LiaoException.h"
#ifndef UINEW_H
#define UINEW_H
#define CHANGEALL 1+2+4+8
namespace liao
{
	class UiOperation
	{
	protected:
		STR message;
		bool show;
	public:
		UiOperation();
		UiOperation(STR message);
		virtual void display() = 0;
		void update(STR message);
		void update(char character);
		void append(STR message);
		void append(char character);
		void remove();
		bool empty();
		void end();
		int size();
		UiOperation& visible();
		UiOperation& invisible();
		void clearContent();
		virtual void clear();
		UiOperation& operator[](bool visible);
		UiOperation& operator+(STR newMessage);
		UiOperation& operator<<(STR newMessage);
		UiOperation& operator<<(char newMessage);
		UiOperation& operator<<(int number);
	public:
		static void clearChar()
		{
			STD cout << "\b \b";
		}
		static void moveBack(int byteSize = 1)
		{
			for (int n = 0; n < byteSize; ++n)
				STD cout << "\b";
		}
		static void clearStr(int byteSize = 1)
		{
			for (int n = 0; n < byteSize; ++n)
				clearChar();
		}
		static void drawEmpty(int byteSize)
		{
			for (int n = 0; n < byteSize; ++n)
				STD cout << " ";
			moveBack(byteSize);
		}
		static void borderLine(int byteSize)
		{
			for (int n = 0; n < byteSize; ++n)
				STD cout << "-";
		}
		static bool confirm(const STR& message)
		{
			STD cout << "\n";
			borderLine(message.size() + 55);
			STD cout << "\n";
			STD cout << message << "(Press Enter or 'Y' for yes, press other key for deny.)";
			STD cout << "\n";
			borderLine(message.size() + 55);
			char result = _getch();
			STD cout << "\n";
			if (result == 'y' || result == 'Y' || result == ENTER)
				return true;
			else
				return false;
		}
		static void hold(const STR& message)
		{
			STD cout << message + CONTINUE;
			_getch();
			clearStr(message.size() + 27);
		}
		static void begin()
		{
			STD cout << "\r";
		}
		static void clearLine(int byteSize)
		{
			begin();
			drawEmpty(byteSize);
		}
		~UiOperation();
	};
	class Dock :public UiOperation
	{
	public:
		Dock();
		Dock(STR defaultDock);
		void display();
	};
	class Loading
	{
		STR bar;
		STR percentage;
		int length;
		int index;
		int maximum;
		int finished;
	private:
		int nextElem();
	public:
		Loading(int, int barlen = 10);
		void update(int);
		void display(double percentage);
		void operator[](int);
	};
	enum class MessageType
	{
		message,
		notice,
		error
	};
	class Message :public UiOperation
	{
		MessageType m_type;
	public:
		Message();
		Message(STR);
		Message(MessageType);
		void display();
		void clear();
		UiOperation& operator[](MessageType outType);
	};
	enum class UiType
	{
		non,
		dock,
		message,
		errorMessage,
		noticeMessage,
		hint
	};
	class Hint :public UiOperation
	{
	public:
		Hint();
		Hint(STR defaultMessage);
		void clear();
		void display();
	};
	class LiaoUi
	{
		Dock dock;//每次更新会擦除之前的dock数据
		Message message;//每次输入会保留上次的模式
		Loading* load;
		Hint hint;//采取全擦除设计，每次更新会被擦除
		onebyte modified;//换行，提示，信息，dock
		bool changeLine;
		bool _visible;
	private:
		bool dockChanged(bool);
		bool messageChanged(bool);
		bool hintChanged(bool);
		void changeDock();
		void changeMessage();
		void changeHint();
	public:
		LiaoUi();
		LiaoUi(STR);
		void ui_clear();
		void ui_redraw();
		void loading_create(int maximum, int barlen);
		void loading_update(int sample);
		void loading_clear();
		void line_change();
		void invisible();
		void visible();
		LiaoUi& display();
		UiOperation& operator[](UiType place);
		LiaoUi& operator<<(STR message);
		inline LiaoUi& operator>>(UiType place)
		{
			return *this;
		}
		~LiaoUi();
	};
	static LiaoUi liao_ui;
}
#endif