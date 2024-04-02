#include "JInput.h"

/*
* OLDVERSION
JInput::JInput()
	:mode(MODE_CMD),key(0)
{}
bool JInput::Enter(bool valid)
{
	if (mode == MODE_TEXT)
	{
		if (inputCache.size() == 0 && resultCache.hasPara())
		{
			ui_notice[false] << "No input received";
			return false;
		}
		else
			return true;
	}
	else if (mode == MODE_PWD|| mode == MODE_STR)
	{
		if (inputCache.size() == 0)
			return true;
		else
		{
			ui_notice[false] << "No input received";
			return false;
		}
	}
	else if (mode<=MODE_CMD)
	{
		if (valid)
		{
			if (mode == MODE_RSTR && inputCache.size() > 0)
				resultCache.addRestrict(inputCache);
			else if (mode == MODE_PARA && inputCache.size() > 0)
				resultCache.insert(inputCache);
			if (this->resultCache.enoughPara())
				return true;
			else
			{
				liao_ui[UiType::message].clear();
				ui_notice[false] << "Insufficient Parameter";
				return false;
			}
		}
		else
		{
			liao_ui[UiType::message].clear();
			ui_notice[false] << "Command Incorrect";
			return false;
		}

	}
	else
	{
		throw new LiaoException("JInput", "Enter", "Unexpected mode!");
	}
}
void JInput::Tab(bool& valid,bool in)
{
	liao_ui[UiType::hint].clear();
	liao_ui[UiType::message].clear();
	auto comTemp =  JCmdList::cmdlist.complete(in);
	valid = comTemp.second;
	this->resultCache.setCmd(comTemp.first);
	inputCache = resultCache.getCmd()->getStd();
	liao_ui[UiType::message][true] << inputCache;
}
void JInput::BackSapce()
{
	if (!liao_ui[UiType::hint].empty())
		liao_ui[UiType::hint].clear();
	liao_ui[UiType::message].remove();
	if (mode == MODE_CMD)
	{
		JCmdList::cmdlist.back();
		if(JCmdList::cmdlist.getCmdLock().size()>0)
			liao_ui[UiType::hint] << JCmdList::cmdlist.getCmdLock();
	}
	if(inputCache.size()!=0)
		this->inputCache.erase(inputCache.end() - 1);
	else
	{
		if (mode == MODE_PARA || mode == MODE_TEXT)
		{
			if (this->resultCache.hasPara()&&inputCache.empty())
			{
				inputCache = resultCache.getPara()[resultCache.getPara().size() - 1];
				resultCache.remove();
			}
		}
	}
	if (mode == MODE_PARA)
	{
		if (resultCache.hasPara())
		{
			inputCache = resultCache.getPara()[resultCache.getPara().size() - 1];
			resultCache.remove();
		}
		if (resultCache.hasRestrict())
			mode = MODE_RSTR;
		else
			mode = MODE_CMD;
	}
	else if(mode == MODE_RSTR)
	{
		resultCache.removeR();
		mode = MODE_CMD;
	}
}
void JInput::Space()
{
	if (mode == MODE_PWD)
		liao_ui[UiType::message] << "*";
	else
		liao_ui[UiType::message] << " ";
	if (mode == MODE_RSTR)
	{
		resultCache.addRestrict(inputCache);
		inputCache.clear();
	}
	else if (this->mode == MODE_TEXT||mode == MODE_PARA)
	{
		this->resultCache.insert(inputCache);
		inputCache.clear();
	}
	else
		inputCache += " ";
	if (mode == MODE_RSTR || mode == MODE_CMD)
	{
		mode = MODE_PARA;
		inputCache.clear();
	}

}
void JInput::clear()
{
	if (mode <= MODE_CMD)
		JCmdList::cmdlist.clear();
	inputCache.clear();
	resultCache.clear();
	liao_ui[UiType::hint].clearContent();
	liao_ui[UiType::message].clearContent();
	key = 0;
}
bool JInput::input()
{
	onebyte curMode = this->mode;
	bool valid = false,in = false;
	for (;;)
	{
		key = _getch();
		if (CONTROL)
		{
			if (key == ESC)
			{
				if (inputCache.size() == 0)
					break;
				else
				{
					liao_ui[UiType::hint].clear();
					liao_ui[UiType::message].clear();

					this->clear();
				}
			}
			else if (key == ENTER && (inputCache.size()>=1))
			{
				if (Enter(valid))
				{
					cout << "\n";
					return true;
				}
				else
					this->clear();
			}
			else if (key == TAB && mode == MODE_CMD)
			{
				Tab(valid,in);
			}
			else if (key == BACKSPACE && inputCache.size() > 0)
			{
				BackSapce();
			}
			else if (key == SPACE &&((
				(mode == MODE_RSTR)
				&&inputCache.size()>0)
				||(mode<=MODE_TEXT&&mode>MODE_CMD)))
			{
				this->Space();
			}
			else if (key == DASH&&mode == MODE_CMD)
			{
				mode = MODE_RSTR;
				inputCache.clear();

			}
			else if (key == -32)
			{
				char temp = _getch();
				if (temp == 72)
				{
					cout << "up\n";
					//上箭头
				}
				else if (temp == 75)
				{
					cout << "left\n";
					//左箭头
				}
				else if (temp == 77)
				{
					cout << "right\n";
					//右箭头
				}
				else if (temp == 80)
				{
					cout << "down\n";
					//下箭头
				}
			}
		}
		else
		{
			liao_ui[UiType::message][true]<<key;
			inputCache += key;
			in = true;
			if (mode == MODE_CMD)
			{
				auto temp = JCmdList::cmdlist.check(key, curStage);
				resultCache.setCmd(temp.first);
				valid = temp.second;
				if(!valid)
					liao_ui[UiType::hint][true]<<JCmdList::cmdlist.getCmdLock();
				else
				{
					UiOperation::drawEmpty(1);
				}
			}
		}
	}
	return false;
}
const CmdPack& JInput::getCmd()
{
	this->clear();
	JCmdList::cmdlist.clear();
	mode = MODE_CMD;
	if (input())
		return this->resultCache;
	else
	{
		this->resultCache.clear();
		return this->resultCache;
	}
}
const WordCmd& JInput::getCmdWord()
{
	if (this->resultCache.hasCmd())
		return resultCache.getCmdWord();
	else
		return WordCmd::Empty;
}
const string& JInput::getString()
{
	this->clear();
	mode == MODE_STR;
	if (input())
		return inputCache;
	else
	{
		this->clear();
		return inputCache;
	}
}
const vector<string>& JInput::getText()
{
	this->clear();
	mode = MODE_TEXT;
	if (input())
		return this->resultCache.getPara();
	else
	{
		this->clear();
		return this->resultCache.getPara();
	}
}
void JInput::updateMode(onebyte mode)
{
	this->mode = mode;
}
void JInput::updateStage(onebyte newStage)
{
	curStage = newStage;
}
bool JInput::paraEmpty()
{
	return resultCache.hasPara();
}
JInput& JInput::operator[](onebyte mode)
{
	updateMode(mode);
	return *this;
}
JInput& JInput::operator>> (string& newString)
{
	newString = getString();
	return *this;
}
JInput& JInput::operator>> (vector<string>& newText)
{
	newText = getText();
	return *this;
}
JInput& JInput::operator>>(CmdPack& newCmd)
{
	newCmd = getCmd();
	return *this;
}
*/