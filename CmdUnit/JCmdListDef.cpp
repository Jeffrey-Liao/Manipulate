#include"JCmdList.h"
#define JCL JCmdList
DoubleLinkList<JCmd> JCmdList::AllCmd =
{
	//Universal
	{"help", "hl", UNIVER_CMD, WC Help, false,1,UserLevel::Guest},
	{ "back","bc",UNIVER_CMD, WC Back, false,0,UserLevel::Guest},
	{ "quit","qt",UNIVER_CMD,WC Quit,false,0,UserLevel::Guest},
	{ "version","vr",UNIVER_CMD,WC Version ,false,0,UserLevel::Guest },
	{ "command","cmd",UNIVER_CMD,WC Command,false,1,UserLevel::Guest},
	{ "log","lg",UNIVER_CMD,WC Log, true,1,UserLevel::Guest},
	{ "exist","es",UNIVER_CMD,WC Exist,true,2,UserLevel::Guest},
	//Main
	{ "change","ch",SHARE_CMD,WC Change,true,1,UserLevel::User},
	{ "undo","ud",SHARE_CMD,WC Undo,false,0,UserLevel::Guest},
	{ "find","fd",SHARE_CMD,WC Find,true,1,UserLevel::Guest},
	{ "remove","rm",SHARE_CMD,WC Remove,true,2,UserLevel::User},
	{ "lock","lc",SHARE_CMD,WC Lock,true,2,UserLevel::Guest},
	{ "unlock","ulc",SHARE_CMD,WC Unlock,true,2,UserLevel::Guest},
	{ "user","us",MAIN_CMD,WC User,false,1,UserLevel::Operator},
	{ "list","ls",MAIN_CMD,WC List,true,1,UserLevel::Guest },
	{ "create","df",MAIN_CMD,WC Create,true,2,UserLevel::Guest },
	{ "author","ath",MAIN_CMD,WC Authorize,true,2,UserLevel::Guest },
	{ "merge","mr",MAIN_CMD,WC Merge,true,1,UserLevel::SuperUser},
	//Table
	{ "append","app",TABLE_CMD,WC Append,true,1,UserLevel::Guest},
	{ "insert","in",TABLE_CMD,WC Insert,true,1,UserLevel::Guest},
	{ "search","sea",TABLE_CMD,WC Search,true,1,UserLevel::Guest},
	{ "print","pr",TABLE_CMD,WC Print,false,1,UserLevel::Guest},
	{ "locate","lo",TABLE_CMD,WC Locate,true,1,UserLevel::Guest}
};
JCmdList JCmdList::cmdlist;
JCmdList::JCmdList()
	:cmdLock(0),match(0),listLock(-1),isShr(false),_index(0)
{
	liao_ui[UiType::message][true] << "Construct command tree branch ";
	liao_ui[UiType::message].clearContent();
	vector<JCmd*> temp;
	liao_ui.loading_create(25, 10);
	for (char m = 'a'; m <='z'; ++m)
	{
		for (int n = 0; n < AllCmd.getSize(); ++n)
		{
			if (AllCmd[n].test(m,0,OVERALL_CMD))
				temp.push_back(&AllCmd[n]);
		}
		if (temp.size() != 0)
		{
			cmdTree.emplace_back(temp);
			temp.clear();
		}
		liao_ui.loading_update(m - 'a');
	}
	liao_ui.loading_clear();
}
int  JCmdList::size()
{
	return this->AllCmd.getSize();
}
bool JCmdList::exist(string cmd)
{
	for (int n = 0; n < AllCmd.getSize(); ++n)
	{
		if(AllCmd[n] == cmd);
			return true;
	}
	return false;
}
 JCmd* const JCmdList::next()
{
	 if (listLock == -1|| listLock == cmdTree.size()-1)
		 listLock = 0;
	 if (cmdLock < cmdTree[listLock].size())
		 return cmdTree[listLock][cmdLock++];
	 else
	 {
		 cmdLock = 0;
		 if(listLock<cmdTree.size()-1)
			return cmdTree[++listLock][cmdLock++];
	 }
}
JCmd& JCmdList::operator[](unsigned int index)
{
	return AllCmd[index];
}
JCmd* const JCmdList::get(string potential)
{
	for (int n = 0; n < this->cmdTree.size(); ++n)
	{
		if (cmdTree[n][0]->test(potential[0],0,OVERALL_CMD))
		{
			for (int m = 0; m < cmdTree[n].size(); ++m)
			{
				if (*cmdTree[n][m] == potential ||
					*cmdTree[n][m] == potential)
					return cmdTree[n][m];
			}
		}
	}
	Debug::debugInfor("JCmdList", "get", "give command incorrect");
	return NULL;
}
vector<JCmd*> JCmdList::getTable()
{
	vector<JCmd*>result;
	for (int n = 0; n < this->AllCmd.getSize(); ++n)
	{
		if (AllCmd[n]==TABLE)
			result.push_back(&AllCmd[n]);
	}
	return result;
}
void JCmdList::back()
{
	if (match >= 0 && _index >= 0)
	{
		if (match == _index)
			--match;
		--_index;
	}
	else
		throw new LiaoException("JCmdList", "back", "either match or index under zero.");
}
void JCmdList::clear()
{
	listLock = -1;
	cmdLock = 0;
	this->match = 0;
	_index = 0;
	isShr = false;
}
pair <JCmd*,bool> JCmdList::check(char key, onebyte type)
{
	double percent=0;
	//当没有匹配字符时
	if (match == 0)
	{
		for (int n = 0; n < this->cmdTree.size(); ++n)
		{
			if (cmdTree[n][0]->test(key,0,type))
			{
				listLock = n;
				match = 1;
				_index = 1;
				break;
			}
		}
	}
	else
	{
		if (match<cmdTree[listLock][cmdLock]->lenSt()&&_index-match<2)
		{
			if (cmdTree[listLock][cmdLock]->test(key,_index,type))
			{
				match++;
				_index++;
			}
			else
			{
				for (int n = cmdLock; n < cmdTree[listLock].size(); ++n)
				{
					if (cmdTree[listLock][n]->test(key, _index, type))
					{
						match++;
						_index++;
						cmdLock = n;
						break;
					}
					if (n == cmdTree[listLock].size() - 1)
					{
						_index++;
					}
				}
			}
		}
	}
	if (listLock >= 0)
		return make_pair(cmdTree[listLock][cmdLock],
			match == _index
			&& (match / cmdTree[listLock][cmdLock]->lenSt() > 0.85
				|| (match / cmdTree[listLock][cmdLock]->lenSh() > 0.85)&&isShr));
	else
		return make_pair((JCmd*)NULL,false);

}
bool JCmdList::isShort()
{
	return this->isShr;
}
const JCmd& JCmdList::lockNext()
{
	if (cmdTree[listLock].size() > cmdLock + 1)
		return *cmdTree[listLock][cmdLock++];
	else
		return *cmdTree[listLock][cmdLock];
}
const JCmd& JCmdList::lockPrev()
{
	if (listLock > 0 && cmdLock > 0 && cmdLock < cmdTree[listLock].size())
		return *cmdTree[listLock][--cmdLock];
	else
		return *cmdTree[listLock][cmdLock];
}
string JCmdList::getCmdLock()
{
	if (listLock>=0&&(match == _index || _index-match <= 2)&&_index > 0)
		return this->cmdTree[listLock][cmdLock]->getStd() + _index;
	else
		return "";
}
pair<JCmd*, bool> JCmdList::complete(bool input)
{
	if (listLock >= 0&&input)
	{
		this->_index = this->match = cmdTree[listLock][cmdLock]->lenSt();
		return make_pair(cmdTree[listLock][cmdLock], true);
	}
	else
	{
		return make_pair(this->next(), true);
	}
}

