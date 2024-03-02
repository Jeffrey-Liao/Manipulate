#include"JCmdList.h"
#define JCL JCmdList

JCL::JCmdList()
	:AllCmd
	({
	//Universal
	{"help", "hl", UNIVER_CMD, WC Help, -1},
	{ "back","bc",UNIVER_CMD, WC Back, 0, },
	{ "quit","qt",UNIVER_CMD,WC Quit,0 },
	{ "version","vr",UNIVER_CMD,WC Version ,0 },
	{ "command","cmd",UNIVER_CMD,WC Command,-1 },
	{ "log","lg",UNIVER_CMD,WC Log,-1 },
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

	{ "liao","lrk",UNIVER_CMD,WC Lrk,0 },
	{ "notfound","nf",0,WC Empty,0 }
	})
{

	Debug::devInfor("Initializing command list");
	vector<JCmd*> temp;
	for (char m = 'a'; m < ('z' + 1); ++m)
	{
		for (int n = 0; n < AllCmd.size(); ++n)
		{
			if (*(AllCmd[n].stdCmd) == m)
				temp.push_back(&AllCmd[n]);
		}
		if (temp.size() != 0)
		{
			cmdTree.emplace_back(temp);
			temp.clear();
		}
	}
}
int JCL::Size()
{
	return this->AllCmd.size() + this->AllTable.size();
}
vector<JCmd>* const JCL::GetCmds()
{
	return &this->AllCmd;
}
vector<JCmd>* JCL::GetTbls()
{
	return &this->AllTable;
}
void JCL::AddTable(const char* fieldName)
{
	AllTable.emplace_back(JCmd(fieldName));
}
JCmd* const JCL::operator[](unsigned int index)
{
	if (index < this->AllCmd.size())
		return &AllCmd[index];
	else if (AllTable.size() != 0 && index < AllTable.size())
		return &AllTable[index];
	else
		return NULL;
}
JCmd* const JCL::operator[](string cmd)
{
	for (int n = 0; n < this->AllCmd.size(); ++n)
	{
		if (AllCmd[n].stdCmd == cmd)
			return &AllCmd[n];
	}
	for (int n = 0; n < this->AllTable.size(); ++n)
	{
		if (AllTable[n].stdCmd == cmd)
			return &AllTable[n];
	}
	return NULL;
}
CC::CmdCheck()
{
	vector<JCmd*> temp;
	for (char m = 'a'; m < ('z' + 1); ++m)
	{
		for (int n = 0; n < cmdListInstance.Size(); ++n)
		{
			if (*cmdListInstance[n]->stdCmd == m)
				temp.push_back(cmdListInstance[n]);
		}
		if (temp.size() != 0)
		{
			cmdTree.emplace_back(temp);
			temp.clear();
		}
	}
}
vector<JCmd*> CC::CmdTest(char newChar, onebyte stage = TABLE)
{
	vector<JCmd*> result;
	for (int n = 0; n < this->cmdTree.size(); ++n)
	{
		if (*cmdTree[n][0]->stdCmd == newChar)
		{
			for (int m = 0; m < this->cmdTree[n].size(); ++m)
			{
				if (cmdTree[n][m]->cmdStage <= stage)
					result.push_back(cmdTree[n][m]);
			}
			break;
		}
	}
	return result;
}
void CC::operator+(JCmd* tableCmd)
{
	for (int n = 0; n < this->cmdTree.size(); ++n)
	{
		if (*cmdTree[n][0]->stdCmd == *tableCmd->stdCmd)
		{
			this->cmdTree[n].push_back(tableCmd);
			break;
		}
		else if (n == cmdTree.size() - 1)
		{
			vector<JCmd*>newBranch;
			newBranch.push_back(tableCmd);
			this->cmdTree.push_back(newBranch);
			newBranch.clear();
		}
	}
}
JCmd* const CC::CmdMatch(string existCmd)
{
	for (int n = 0; n < cmdTree.size(); ++n)
	{
		if (*cmdTree[n][0]->stdCmd == existCmd[0])
		{
			for (int m = 0; m < cmdTree[n].size(); ++m)
			{
				if (cmdTree[n][m]->stdCmd == existCmd)
					return cmdTree[n][m];
			}
		}
	}
	return NULL;
}
JCmd* const  CC::operator [](string checkCmd)
{
	return CmdMatch(checkCmd);
}

onebyte CU::getStage()
{
	return this->Stage;
}
bool CU::isUserActive()
{
	return this->CurrentUser.isActive();
}
bool CU::command(string requirement)
{
	if (requirement == "")
	{
		for (int n = 0; n < cmdListInstance.GetCmds()->size(); ++n)
		{
			if (cmdListInstance[n]->cmdStage == this->Stage)
				cout << ">>>\t" << cmdListInstance[n]->stdCmd << "\n";
		}
		return true;
	}
	else
	{
		int index = (int)WC Command, para = 0;
		if (requirement == "a" || requirement == "all")
		{
			for (int n = 0; n < cmdListInstance.GetCmds()->size() - CMD_RESERVED; ++n)
				cout << ">>>\t" << cmdListInstance[n]->stdCmd << "\n";
		}
		else if (requirement == "l" || requirement == "ls" || requirement == "list")
		{
			cout << "\t" << "command\tshort\tstage\tnumber of para\n";
			for (int n = 0; n < cmdListInstance.GetCmds()->size() - CMD_RESERVED; ++n)
			{
				if (cmdListInstance[n]->cmdStage == this->Stage)
				{
					cout << ">>>\t" << cmdListInstance[n]->stdCmd << "\t"
						<< cmdListInstance[n]->shrCmd << "\t"
						<< (int)cmdListInstance[n]->cmdStage << "\t"
						<< (int)cmdListInstance[n]->paraNum << "\n";
				}
			}
		}
		else if (requirement == "la" || requirement == "listall")
		{
			cout << "\t" << "command\t\tshort\tstage\tnumber of para\n";
			for (int n = 0; n < cmdListInstance.GetCmds()->size() - CMD_RESERVED; ++n)
			{
				cout << ">>>\t" << cmdListInstance[n]->stdCmd << "\t\t"
					<< cmdListInstance[n]->shrCmd << "\t"
					<< (int)cmdListInstance[n]->cmdStage << "\t"
					<< (int)cmdListInstance[n]->paraNum << "\n";
			}
		}
		else if (requirement == "u" || requirement == "universal")
		{
			for (int n = 0; n < cmdListInstance.GetCmds()->size() - CMD_RESERVED; ++n)
			{
				if (cmdListInstance[n]->cmdStage == UNIVER_CMD)
					cout << ">>>\t" << cmdListInstance[n]->stdCmd << "\n";
			}
		}
		else if (requirement == "m" || requirement == "main")
		{
			for (int n = 0; n < cmdListInstance.GetCmds()->size() - CMD_RESERVED; ++n)
			{
				if (cmdListInstance[n]->cmdStage >= MAIN_CMD && cmdListInstance[n]->cmdStage <= SHARE_CMD)
					cout << ">>>\t" << cmdListInstance[n]->stdCmd << "\n";
			}
		}
		else if (requirement == "t" || requirement == "table")
		{
			for (int n = 0; n < cmdListInstance.GetCmds()->size() - CMD_RESERVED; ++n)
			{
				if (cmdListInstance[n]->cmdStage >= SHARE_CMD)
					cout << ">>>\t" << cmdListInstance[n]->stdCmd << "\n";
			}
		}
		else
		{
			cout << "Incorrect parameter";
			return false;
		}

	}
}

void CU::help(string existCmd)
{
	if (existCmd.size() == 0)
	{
		char temp[100] = { '\0' };
		ifstream file;
		if (sysLanguage)
			file.open("helper.txt");
		else
			file.open("helper_en.txt");
		while (!file.eof())
		{
			file.getline(temp, 100);
			if (temp[0] == '~')
			{
				if (_getch() == 27)
					break;
				cout << "-----------------------------------------------------------------";
				cout << "\n";
			}
			else
				cout << temp << "\n";
		}
		cout << "\n\n";
		file.close();
	}
	else
	{
		char temp[100] = { '\0' };
		auto result = CmdCheck::Checker[existCmd];
		if (result != NULL)
		{
			fstream file, file2;
			if (result->cmdStage == UNIVER_CMD)
			{
				if (sysLanguage)
					file.open("universal.txt");
				else
					file.open("universal_en.txt");
			}
			else if (result->cmdStage >= MAIN_CMD && result->cmdStage <= SHARE_CMD)
			{
				if (sysLanguage)
					file.open("share.txt"), file2.open("main.txt");
				else
					file.open("share_en.txt"), file2.open("main_en.txt");
			}
			else if (result->cmdStage >= SHARE_CMD && result->cmdStage <= TABLE_CMD)
			{
				if (sysLanguage)
					file.open("share.txt"), file2.open("table.txt");
				else
					file.open("share_en.txt"), file2.open("table_en.txt");
			}
			bool checked = false;
			while (!file.eof())
			{
				file.getline(temp, 100);
				if (existCmd == temp)
				{
					cout << "# " << temp << "\n";
					while (1)
					{
						file.getline(temp, 100);
						if (temp[0] == '~' || file.eof())
						{
							break;
						}
						cout << temp << "\n";
					}
					checked = true;
					break;
				}
			}
			while (!file2.eof() && !checked)
			{
				file2.getline(temp, 100);
				if (existCmd == temp)
				{
					cout << "# " << temp << "\n";
					while (1)
					{
						file2.getline(temp, 100);
						if (temp[0] == '~' || file2.eof())
						{
							break;
						}
						cout << temp << "\n";
					}
					break;
				}
			}
			file.close();
			file2.close();
		}
		else
		{
			cout << "Wrong Command\n";
		}
	}
}
void CU::version()
{
	char temp[500];
	ifstream file("devInfor.txt");
	while (!file.eof())
	{
		file.getline(temp, 500);
		cout << temp << "\n";
	}
	file.close();
}
bool CU::exist(char restriction, string paraString)
{
	if (restriction == 'c')
	{
		if (CmdCheck::Checker[paraString] != NULL)
			cout << "Command Exist\n";
		else
			cout << "Command Not Exist\n";
		return CmdCheck::Checker[paraString] != NULL;
	}
	else if (restriction == 'u')
		cout << "Coming soon\n";
	else if (restriction == 't')
		cout << "Coming soon\n";
	return true;
}
int CU::log(string restriction)
{

	return 0;
}
void CU::liao()
{
	cout << "I want to build a new world with code!\n";
	cout << "I was built a lot of worlds.\nSome of them are in my mind.\nSome of them are in Minecraft.\nBut now it is in front of you.\nAnd I am not that shit man anymore. Never!\n";
}