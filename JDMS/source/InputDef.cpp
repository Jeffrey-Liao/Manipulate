#include "JInput.h"
JInput JInput::liao_input;
JInput::JInput()
	:control(true),key(0)
{}
JCmd* JInput::Enter(string& cache, const bool cmdMode)
{
	if ((curCmd.second >= PASSRATE&&control&&cmdCache.size()!=0) || (!control && (inputCache.size() != 0 || cache.size() != 0)))
	{
		JCmdList::cmdlist.clear();
		if (cache.size() != 0 && !control)
		{
			if(cmdMode||inputCache.size()!=0)
				cache.erase(cache.begin());
			inputCache.push_back(cache);
		}
		UiHint::ui_hint.end();
		if (cmdMode)
			return curCmd.first;
		else
			return NULL;
	}
	else
	{
		JUi::strClear(cache.size());
		UiNoticeMessage::ui_notice[false] << "command incorrect";
		cache.clear();
		cmdCache.clear();
		JCmdList::cmdlist.clear();
		control = true;
		return NULL;
	}
}
void JInput::Tab(string& cache)
{
	curCmd = JCmdList::cmdlist.complete();
	JUi::strClear(cache.size());
	cache = cmdCache = curCmd.first->stdCmd;
	UiCharMessage::ui_char << cmdCache;
	JUi::drawEmpty(cmdCache.size() + 2);
	ui_message << curCmd.first->stdCmd;
}
void JInput::BackSapce(string& cache, const bool cmdMode)
{
	UiCharMessage::ui_char.remove();
	if (!cache.empty())
		cache.erase(cache.size() - 1);
	else
		throw LiaoException("JInput", "input", "cannot remove character from an empty input cache");
	if (control)//control mode
	{
		if (cache.size() >= 0 && cache.size() < cmdCache.size())
		{
			if(JCmdList::cmdlist.start())
				JCmdList::cmdlist.back();
			JUi::drawEmpty(20);
			UiHint::ui_hint << JCmdList::cmdlist.getCmdLock();
			cmdCache.erase(cmdCache.size() - 1);
		}
		else
			JUi::drawEmpty(20);
	}
	else// input mode
	{
		if (cache.size() == 0 && !control)
		{
			if (inputCache.size() == 0 && cmdMode)
			{
				control = true;
				cache = cmdCache;
			}
			else
			{
				if (inputCache.size() != 0)
				{
					cache = " "+ inputCache[inputCache.size() - 1];
					inputCache.erase(inputCache.end() - 1);
				}
			}
		}
	}
}
void JInput::clear()
{
	this->control = true;
}
JCmd* JInput::input(const bool cmdMode)
{
	inputCache.clear();
	cmdCache.clear();
	string cache;
	control = cmdMode;
	key = 0;
	for (; key != ESC;)
	{
		key = _getch();
		if (CONTROL)
		{
			if (key == ENTER && (cache.size() >= 1||cmdCache.size()>=1))
			{
				JCmd* temp = Enter(cache, cmdMode);
				if (temp == NULL && !cmdMode)
					return NULL;
				else if (temp == NULL && control)
					continue;
				else if (temp != NULL)
					return temp;
			}
			else if (key == TAB && JCmdList::cmdlist.getCmdLock().size() != 0 && cache.size() >= 0 && control)
			{
				Tab(cache);
			}
			else if (key == BACKSPACE && ((cache.size() > 0&&control)||((inputCache.size() != 0 || cache.size() >0)&& !control)))
			{
				BackSapce(cache, cmdMode);
			}
			else if (key == SPACE && ((curCmd.second == 1 && control) || (!control && cache.size() != 0)))
			{
				UiCharMessage::ui_char <<' ';
				if (control)
					control = false,cache.clear();
				else
				{
					if(!cmdMode&&inputCache.size() || cmdMode)
						cache.erase(cache.begin());
					inputCache.push_back(cache);
				}
				cache.clear();
				cache += ' ';
			}
		}
		else
		{
			UiCharMessage::ui_char.showChar(key);
			cache += key;
			if (control)
			{
				cmdCache += key;
				curCmd = JCmdList::cmdlist.check(key, curStage);
				UiHint::ui_hint << JCmdList::cmdlist.getCmdLock();
			}
		}
	}
	return NULL;
}
vector<string>& JInput::getParameter()
{
	return inputCache;
}
void JInput::updateStage(onebyte newStage)
{
	curStage = newStage;
}
bool JInput::paraEmpty()
{
	return this->inputCache.size() == 0;
}