#include"UiUnit.h"
using namespace std;
namespace liao
{
#pragma region NEWUIOPER
	UiOperation::UiOperation()
		:show(false)
	{
		message = "";
	}
	UiOperation::UiOperation(string message)
		:show(false)
	{
		update(message);
	}
	UiOperation::~UiOperation()
	{
		this->clear();
	}
	int UiOperation::size()
	{
		return this->message.size();
	}
	void UiOperation::update(char character)
	{
		this->message = character;
	}
	void UiOperation::update(string message)
	{
		this->message = message;
	}
	void UiOperation::append(string message)
	{
		this->message += message;
	}
	void UiOperation::append(char character)
	{
		this->message += character;
	}
	UiOperation& UiOperation::visible()
	{
		this->show = true;
		return *this;
	}
	bool UiOperation::empty()
	{
		return message.empty();
	}
	void UiOperation::end()
	{
		cout << "\n";
	}
	UiOperation& UiOperation::invisible()
	{
		this->show = false;
		return *this;
	}
	void UiOperation::remove()
	{
		this->message.erase(message.end() - 1);
		this->clearChar();
	}
	void UiOperation::clearContent()
	{
		message.clear();
	}
	void UiOperation::clear()
	{
		clearStr(message.size());
		clearContent();
	}
	UiOperation& UiOperation::operator[](bool visible)
	{
		this->show = visible;
		return *this;
	}
	UiOperation& UiOperation::operator<<(const string message)
	{
		this->update(message);
		if (show)
		{
			this->display();
		}

		return *this;
	}
	UiOperation& UiOperation::operator<<(const char character)
	{
		this->append(character);
		if (show)
		{
			cout << character;
		}
		return *this;
	}
	UiOperation& UiOperation::operator<<(int number)
	{
		this->append(to_string(number));
		if (show)
		{
			this->display();
		}
		return *this;
	}
	UiOperation& UiOperation::operator+(string newMessage)
	{
		this->append(newMessage);
		return *this;
	}
#pragma endregion
#pragma region NEWUIDOCK
	Dock::Dock()
		:UiOperation()
	{
	}
	Dock::Dock(string defaultDock)
		:UiOperation(defaultDock)
	{
	}
	void Dock::display()
	{
		if (!this->message.empty())
			moveBack(this->message.size());
		cout << this->message << "::";
	}
#pragma endregion
#pragma region NEWUILOAD
	Loading::Loading(int maximum, int barlen)
		:maximum(maximum), length(barlen), finished(0), index(0)
	{
		bar = "[";
		for (int n = 0; n < barlen; ++n)
		{
			bar += " - ";
		}
		bar += "]";
		percentage = "0%";
		cout << bar << to_string(0) + "%";
	}
	int Loading::nextElem()
	{
		if (index == 0)
			index = finished + 2;
		else
			index += 3;
		finished++;
		return index;
	}
	void Loading::update(int sample)
	{
		display(double(sample + 1) / double(maximum));
	}
	void Loading::display(double percentage)
	{
		UiOperation::moveBack(this->bar.size() + this->percentage.size());
		if (percentage <= 1)
			this->percentage = to_string(int(percentage * 100)) + "%";
		else
			this->percentage = to_string(100) + "%";
		while ((double(finished) / double(length)) < percentage && finished < length)
			bar[nextElem()] = '>';
		cout << bar << this->percentage;
	}
	void Loading::operator[](int sample)
	{
		update(sample);
	}
#pragma endregion
#pragma region NEWUIMESSAGE
	Message::Message()
		:UiOperation(), m_type(MessageType::message)
	{}
	Message::Message(string defualtMes)
		:UiOperation(defualtMes), m_type(MessageType::message)
	{}
	Message::Message(MessageType newType)
		:UiOperation(), m_type(newType)
	{}
	void Message::display()
	{
		if (m_type == MessageType::message)
			cout << message;
		else if (m_type == MessageType::notice)
		{
			message = "{NOTICE} > (" + message + ")";
			hold(message);
		}
		else if (m_type == MessageType::error)
		{
			cout << "[ERROR] > (" << message << ")";
		}
	}
	void Message::clear()
	{
		UiOperation::clear();
		m_type = MessageType::message;
	}
	UiOperation& Message::operator[](MessageType outType)
	{
		this->m_type = outType;
		return *this;
	}
#pragma endregion
#pragma region NEWUIHINT
	Hint::Hint()
	{
		this->message = "";
	}
	Hint::Hint(string defaultMessage)
		:UiOperation(defaultMessage)
	{}
	void Hint::display()
	{
		cout << "-" << message;
		moveBack(message.size() + 1);
	}
	void Hint::clear()
	{
		drawEmpty(message.size() + 1);
	}
#pragma endregion

#pragma region NEWUICENTER
	LiaoUi::LiaoUi()
		:load(NULL), modified(0), changeLine(false), _visible(true)
	{}
	LiaoUi::LiaoUi(string defaultStr)
		:load(NULL), message(defaultStr), modified(0), changeLine(false), _visible(true)
	{}
	LiaoUi::~LiaoUi()
	{
		if (load)
			delete load;
	}
	bool LiaoUi::dockChanged(bool reverse = false)
	{
		int test = 1;
		if (reverse)
			modified -= 1;
		return modified & test;

	}
	bool LiaoUi::messageChanged(bool reverse = false)
	{
		int test = 1;
		if (reverse)
			modified -= (1 << 1);
		else
			test = 1;
		return modified & (test << 1);
	}
	bool LiaoUi::hintChanged(bool reverse = false)
	{
		int test = 1;
		if (reverse)
			modified -= (1 << 2);
		return modified & (test << 2);
	}
	void LiaoUi::changeDock()
	{
		int test = 1;
		modified |= test;
	}
	void LiaoUi::changeMessage()
	{
		int test = 1;
		modified |= (test << 1);
	}
	void LiaoUi::changeHint()
	{
		int test = 1;
		modified |= (test << 2);
	}
	void LiaoUi::ui_clear()
	{
		UiOperation::begin();
		UiOperation::drawEmpty(dock.size() + message.size() + hint.size());
		modified = 0;
		message.clearContent();
		hint.clear();
		changeLine = false;
	}
	void LiaoUi::ui_redraw()
	{
		UiOperation::begin();
		UiOperation::drawEmpty(dock.size() + message.size() + hint.size());
		modified = CHANGEALL;
		changeLine = false;
	}
	void LiaoUi::loading_create(int maximum, int barlen)
	{
		if (this->load)
			delete load;
		this->load = new Loading(maximum, barlen);
	}
	void LiaoUi::loading_update(int sample)
	{
		this->load->update(sample);
	}
	void LiaoUi::loading_clear()
	{
		cout << "\n";
		delete this->load;
		this->load = NULL;
	}
	void LiaoUi::line_change()
	{
		hint.clear();
		message.end();
		hint.clearContent();
		message.clearContent();
		changeDock();
		display();
	}
	void LiaoUi::invisible()
	{
		this->_visible = false;
	}
	void LiaoUi::visible()
	{
		this->_visible = true;
	}
	LiaoUi& LiaoUi::display()
	{
		if (dockChanged())
		{
			dock.display();
			dockChanged(true);
		}
		if (messageChanged())
		{
			message.display();
			if (changeLine)
				line_change();
			else
				messageChanged(true);
		}
		if (hintChanged() && hint.size() > 0)
		{
			hint.display();
			hintChanged(true);
		}
		return *this;
	}
	UiOperation& LiaoUi::operator[](UiType place)
	{
		if (place == UiType::hint)
		{
			changeHint();
			return this->hint[_visible];
		}
		else if (place == UiType::dock)
		{
			changeDock();
			return this->dock[_visible];
		}
		else if (place == UiType::message || place == UiType::non)
		{
			changeMessage();
			return this->message.visible();
		}
		else if (place == UiType::errorMessage)
		{
			changeMessage();
			return this->message[MessageType::error][_visible];
		}
		else if (place == UiType::noticeMessage)
		{
			changeMessage();
			return this->message[MessageType::notice][_visible];
		}
	}
	LiaoUi& LiaoUi::operator<<(string message)
	{
		this->message.visible() << message;
		return *this;
	}
#pragma endregion

}
