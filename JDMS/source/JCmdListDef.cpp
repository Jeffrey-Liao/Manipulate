#include"JCmdList.h"
#define JCL JCmdList
DoubleLinkList<JCmd> JCmdList::AllCmd =
{
	//Universal
	{"help", "hl", UNIVER_CMD, WC Help, -1},
	{ "back","bc",UNIVER_CMD, WC Back, 0, },
	{ "quit","qt",UNIVER_CMD,WC Quit,0 },
	{ "version","vr",UNIVER_CMD,WC Version ,0 },
	{ "command","cmd",UNIVER_CMD,WC Command,-1 },
	{ "log","lg",UNIVER_CMD,WC Log, 1 },
	{ "exist","es",UNIVER_CMD,WC Exist,2 },
	//Main
	{ "change","ch",SHARE_CMD,WC Change,1 },
	{ "undo","ud",SHARE_CMD,WC Undo,0 },
	{ "find","fd",SHARE_CMD,WC Find,1 },
	{ "remove","rm",SHARE_CMD,WC Remove,2 },
	{ "lock","lc",SHARE_CMD,WC Lock,2 },
	{ "unlock","ulc",SHARE_CMD,WC Unlock,2 },
	{ "user","us",MAIN_CMD,WC User,-1 },
	{ "list","ls",MAIN_CMD,WC List,1 },
	{ "create","df",MAIN_CMD,WC Create,2 },
	{ "author","ath",MAIN_CMD,WC Authorize,2 },
	{ "merge","mr",MAIN_CMD,WC Merge,1 },
	//Table
	{ "append","app",TABLE_CMD,WC Append,1 },
	{ "insert","in",TABLE_CMD,WC Insert,2 },
	{ "search","sea",TABLE_CMD,WC Search,1 },
	{ "print","pr",TABLE_CMD,WC Print,-1 },
	{ "locate","lo",TABLE_CMD,WC Locate,1 },

	{ "liao","lrk",HIDDEN,WC Lrk,0 },
	{ "notfound","nf",HIDDEN,WC Empty,0 }
};
JCmdList JCmdList::cmdlist;
JCL::JCmdList()
	:cmdLock(0),match(0),listLock(-1),isShr(false),_index(0)
{
	ui_message << "Construct command tree branch ";
	ui_message.messageClear();
	vector<JCmd*> temp;
	for (char m = 'a'; m <='z'; ++m)
	{
		for (int n = 0; n < AllCmd.getSize(); ++n)
		{
			if (*(AllCmd[n].stdCmd) == m)
				temp.push_back(&AllCmd[n]);
		}
		if (temp.size() != 0)
		{
			cmdTree.emplace_back(temp);
			temp.clear();
		}
		ui_loading[25]<<(m-'a');
	}
	ui_loading.end();
}
int JCL::size()
{
	return this->AllCmd.getSize();
}
JCmd& JCmdList::operator[](unsigned int index)
{
	return AllCmd[index];
}
const JCmd* const JCL::get(string potential)
{
	for (int n = 0; n < this->cmdTree.size(); ++n)
	{
		if (*cmdTree[n][0]->stdCmd == potential[0])
		{
			for (int m = 0; m < cmdTree[n].size(); ++m)
			{
				if (potential == cmdTree[n][m]->stdCmd ||
					potential == cmdTree[n][m]->shrCmd)
					return cmdTree[n][m];
			}
		}
	}
	Debug::debugInfor("JCmdList", "get", "give command incorrect");
	return NULL;
}
vector<string> JCL::getTable()
{
	vector<string>result;
	for (int n = 0; n < this->AllCmd.getSize(); ++n)
	{
		if (AllCmd[n].cmdType == TABLE)
			result.push_back(AllCmd[n].stdCmd);
	}
	return result;
}
void JCmdList::back()
{
	if (match >= 0 && _index >= 0)
	{
		if (match <= _index)
			--match;
		--_index;
	}
	else
		throw new LiaoException("JCmdList", "back", "either match or index under zero.");
}
void JCmdList::clear()
{
	listLock = 0;
	cmdLock = 0;
	this->match = 0;
	_index = 0;
	isShr = false;
}
pair <JCmd*,double> JCmdList::check(char key, onebyte type)
{
	double percent=0;
	if (match == 0)
	{
		for (int n = 0; n < this->cmdTree.size(); ++n)
		{
			if ((*cmdTree[n][0]->stdCmd == key
				|| *cmdTree[n][0]->shrCmd == key)&& cmdTree[n][0]->cmdType<=type)
			{
				if (*cmdTree[n][0]->shrCmd == key && *cmdTree[n][0]->stdCmd != *cmdTree[n][0]->shrCmd == key)
					isShr = true;
				listLock = n;
				match = 1;
				_index = 1;
				break;
			}
		}
	}
	else
	{
		if (match <= _index && (isShr &&_index <= strlen(cmdTree[listLock][cmdLock]->shrCmd))
			|| _index <= strlen(cmdTree[listLock][cmdLock]->stdCmd))
		{
			if (*(cmdTree[listLock][cmdLock]->stdCmd + _index) == key || *(cmdTree[listLock][cmdLock]->shrCmd + _index) == key)
			{
				match++;
				_index++;
			}
			else
			{
				for (int n = cmdLock; n < cmdTree[listLock].size(); ++n)
				{
					if (*(cmdTree[listLock][n]->stdCmd + _index) == key || *(cmdTree[listLock][n]->shrCmd + _index) == key)
					{
						match++;
						_index++;
						cmdLock = n;
						break;
					}
				}
			}
		}
	}
	if (listLock >= 0)
	{
		if(isShr)
			percent = (double) match / (double)strlen(cmdTree[listLock][cmdLock]->shrCmd);
		else
			percent = (double) match / (double)strlen(cmdTree[listLock][cmdLock]->stdCmd);
		return make_pair(cmdTree[listLock][cmdLock], percent);
	}
	else
		return make_pair((JCmd*)NULL, 0.0);

}
bool JCmdList::isShort()
{
	return this->isShr;
}
JCmd& JCmdList::lockNext()
{
	if (cmdTree[listLock].size() > cmdLock + 1)
		return *cmdTree[listLock][cmdLock++];
	else
	{
		throw new LiaoException("JCmd", "lockNext", "cmdlock overflow");
		return *cmdTree[listLock][cmdLock];
	}
}
JCmd& JCmdList::lockPrev()
{
	if (listLock > 0)
		return *cmdTree[listLock][cmdLock];
	else
	{
		throw new LiaoException("JCmd", "lockPrev", "cmdlock underflow");
		return *cmdTree[listLock][cmdLock];
	}
}
string JCmdList::getCmdLock()
{
	if (match == _index&&_index >0)
		return this->cmdTree[listLock][cmdLock]->stdCmd + _index;
	else
		return "";
}
pair<JCmd*, double> JCmdList::complete()
{
	if (listLock >= 0)
	{
		this->_index = this->match = strlen(cmdTree[listLock][cmdLock]->stdCmd);
		return make_pair(cmdTree[listLock][cmdLock], 1);
	}
	else
		throw new LiaoException("JCmdList", "complete", "No locked command");
}

