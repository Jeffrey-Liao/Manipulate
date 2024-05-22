#include"JCenter.h"
#define CMD_RESERVED 2
Center::Center()
	:currentUser(NULL),Language(sysLan::English)
{
}
void Center::InsufficientPara()
{
	liao_ui[UiType::message] << "Insufficient Para";
}
void Center::border()
{
	UiOperation::borderLine(100);
	liao_ui.line_change();
}
void Center::receiveCmd()
{
	JCmdList::cmdlist.clear();
	liao_input>> currentCmd;
}
void Center::receiveInput()
{
	liao_input[MODE_TEXT]>>currentCmd.getPara();
}
void iterationUpdate()
{
	fstream file("./resource/versionInf.txt", ios::in | ios::out);
	int temp = 0;
	file >> temp;
	file.seekg(0, std::ios::beg);
	file << temp + 1 << "\n";
	file << Debug::Timer(false)<<"\n";
	file.close();
}
void Center::help(vector<string>& parameters)
{
	if (parameters.size() == 0)
	{
		char temp[100] = { '\0' };
		ifstream file;
		if (Language == sysLan::Chinese)
			file.open("./resource/helper/helper.txt");
		else
			file.open("./resource/helper/helper_en.txt");
		if (file.fail())
			liao_ui[UiType::errorMessage][true] << "Cannot find help file. Please contact developer.";
		else
		{
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
		}
		file.close();
	}
	else
	{
		char temp[100] = { '\0' };
		auto result = JCmdList::cmdlist.get(parameters[0]);
		if (result != NULL)
		{
			fstream file, file2;
			if (result->usable(UNIVER_CMD))
			{
				if (Language == sysLan::Chinese)
					file.open("./resource/helper/universal.txt");
				else
					file.open("./resource/helper/universal_en.txt");
			}
			else if (result->usable( MAIN_CMD) && result->usable(SHARE_CMD))
			{
				if (Language == sysLan::Chinese)
					file.open("./resource/helper/share.txt"), file2.open("./resource/helper/main.txt");
				else
					file.open("./resource/helper/share_en.txt"), file2.open("./resource/helper/main_en.txt");
			}
			else if (result->usable(SHARE_CMD) && result->usable(TABLE_CMD))
			{
				if (Language == sysLan::Chinese)
					file.open("./resource/helper/share.txt"), file2.open("./resource/helper/table.txt");
				else
					file.open("./resource/helper/share_en.txt"), file2.open("./resource/helper/table_en.txt");
			}
			if (file.fail() || file2.fail())
			{
				throw new LiaoException("JCenter", "help", "Cannot find data file");
			}
			else
			{
				bool checked = false;
				while (!file.eof())
				{
					file.getline(temp, 100);
					if (parameters[0] == temp)
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
					if (parameters[0] == temp)
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
		}
		else
			cout << "Wrong Command\n";
	}
}
bool Center::command(string restriction,vector<string>& parameters)
{
	if (currentCmd.getCmd()->enoughPara(parameters.size()))
	{
		if (parameters.size() ==0)
		{
			for (int n = 0; n < JCmdList::cmdlist.size(); ++n)
			{
				if (JCmdList::cmdlist[n].usable(curStage))
					cout << ">>>\t" << JCmdList::cmdlist[n].print(PRINT_CMD) << "\n";
			}
			return true;
		}
		else
		{
			if (restriction == "a" || restriction == "all")
			{
				for (int n = 0; n < JCmdList::cmdlist.size(); ++n)
					cout << ">>>\t" << JCmdList::cmdlist[n].print(PRINT_CMD) << "\n";
			}
			else if (restriction == "l" || restriction == "ls" || restriction == "list")
			{
				cout << "\t" << "command\tshort\tstage\tnumber of para\n";
				for (int n = 0; n < JCmdList::cmdlist.size(); ++n)
				{
					if (JCmdList::cmdlist[n].usable(curStage))
						liao_ui[UiType::message] << JCmdList::cmdlist[n].print(PRINT_ALL);
				}
			}
			else if (restriction == "la" || restriction == "listall")
			{
				cout << "\t" << "command\t\tshort\tstage\tnumber of para\n";
				for (int n = 0; n < JCmdList::cmdlist.size(); ++n)
				{
					liao_ui[UiType::message] << JCmdList::cmdlist[n].print(PRINT_ALL);
				}
			}
			else if (restriction == "u" || restriction == "universal")
			{
				for (int n = 0; n < JCmdList::cmdlist.size(); ++n)
				{
					if (JCmdList::cmdlist[n].usable(UNIVER_CMD))
						cout << ">>>\t" << JCmdList::cmdlist[n].print(PRINT_CMD) << "\n";
				}
			}
			else if (restriction == "m" || restriction == "main")
			{
				for (int n = 0; n < JCmdList::cmdlist.size() ; ++n)
				{
					if (JCmdList::cmdlist[n].usable(MAIN_CMD) && JCmdList::cmdlist[n].usable(SHARE_CMD))
						cout << ">>>\t" << JCmdList::cmdlist[n].print(PRINT_CMD)<< "\n";
				}
			}
			else if (restriction == "t" || restriction == "table")
			{
				for (int n = 0; n < JCmdList::cmdlist.size(); ++n)
				{
					if (JCmdList::cmdlist[n].usable(SHARE_CMD))
						cout << ">>>\t" << JCmdList::cmdlist[n].print(PRINT_CMD) << "\n";
				}
			}
			else
			{
				cout << "Incorrect parameter";
				return false;
			}

		}
	}
	else
	{
		ui_notice.error();
		ui_notice << "Insufficient parameters for {command}";
	}
}
void Center::execute()
{
	iterationUpdate();
	userlist.read();
	if (userlist.empty())
	{
		liao_ui[UiType::dock][true] << "Help";
		liao_ui[UiType::message][true] << "Try to type 'help' command in the terminal, if you are new user\n";
		liao_ui.line_change();
	}
	liao_ui[UiType::dock][true] << "No user Login";
	while (1)
	{
		try
		{
			receiveCmd();
			if (currentCmd.hasCmd() && currentCmd.getCmdWord() != WordCmd::Quit)
			{
				if (currentCmd.getCmdWord() == WordCmd::Help)
					help(currentCmd.getPara());
				else if (currentCmd.getCmdWord() == WordCmd::Command)
					command(currentCmd.getRestrict(),currentCmd.getPara());
				else if (currentCmd.getCmdWord() == WordCmd::Version)
					version();
				else if (currentCmd.getCmdWord() == WordCmd::Exist)
					exist(currentCmd.getRestrict(), currentCmd.getPara());
				else if (currentCmd.getCmdWord() == WordCmd::Log)
					login(currentCmd.getRestrict(), currentCmd.getPara());
				border();
			}
			else
			{
				if (UiOperation::confirm("Exit the system?"))
					break;
				liao_ui.line_change();
			}
			currentCmd.clear();
		}
		catch (LiaoException* fatalError)
		{
			cout << "\n" << fatalError->getErrorMessage();
			delete fatalError;
			system("pause");
			liao_ui.line_change();
		}
		catch (LiaoException fatalError)
		{
			cout << "\n" << fatalError.getErrorMessage();
			system("pause");
			liao_ui.line_change();
		}
	}
}
void Center::version()
{
	string version = "v0.32403_demo";
	fstream file("./resource/versionInf.txt",ios::in|ios::out);
	if (file.fail())
		throw new LiaoException("Center", "version", "Target file missing");
	int temp;
	string date;
	file >> temp;
	file >> date;
	cout << version + " " + to_string(temp)+"->"+ date;
	char updateInfor[500];
	while (!file.eof())
	{
		file.getline(updateInfor,500);
		cout << updateInfor<<"\n";
	}
	file.close();
}
bool Center::exist(string restriction,vector<string>& parameter)
{
	if (currentCmd.getCmd()->enoughPara(parameter.size()))
	{
		if (restriction == "c" || restriction == "command")
		{
			if (JCmdList::cmdlist.exist(parameter[1]))
			{
				liao_ui[UiType::message] << "Command Exist\n";
				return true;
			}
			else
			{
				liao_ui[UiType::message] << "Command Not Exist\n";
				return false;
			}
		}
		else if (restriction == "u" || restriction == "user")
		{
			bool result = userlist.getIndex(parameter[1]) != -1;
			if (result)
				liao_ui[UiType::message] << "User exist";
			else
				liao_ui[UiType::message] << "User not exist";
			liao_ui[UiType::message].end();
			return result;
		}
		else if (restriction == "t" || restriction == "table")
			cout << "Coming soon\n";
		return true;
	}
	else
	{
		ui_notice.error();
		ui_notice << "Insufficient parameters for {exist}";
		return false;
	}
}
bool Center::logInterface(string& userNameT, string& passwordT)
{
	liao_ui[UiType::message] << "Please give your user name:";
	liao_input[MODE_STR] >> userNameT;
	if (userNameT != "")
	{
		liao_input[MODE_PWD] >> passwordT;
		if (passwordT != "")
			return true;
	}
	return false;
}
void Center::changeDockInfor()
{
	if (currentUser != NULL)
		liao_ui[UiType::dock].update( currentUser->getUserName());
	else
		liao_ui[UiType::dock].update("No user Login");
}
bool Center::login(string restriction,vector<string>& parameter)
{
	if (currentCmd.getCmd()->enoughPara(parameter.size()) )
	{
		bool result = false;
		string userNameT, passwordT;
		if (restriction == "i" || restriction == "in"&&currentUser == NULL)
		{
			while (1)
			{
				if (!logInterface(userNameT, passwordT))
					break;
				if (!userlist.login(userNameT, passwordT))
				{
					liao_ui[UiType::message] << "User name or password incorrect";
					if (!JUi::confirm("Do you want to try again?"))
						break;
				}
				else 
				{
					if(currentUser == NULL)
						currentUser = userlist.getActive()[0];
					curStage = SHARE_CMD;
					changeDockInfor();
					return true;
				}

			}
		}
		else if (restriction == "u" || restriction == "up")
		{
			while (1)
			{
				if (!logInterface(userNameT, passwordT))
					break;
				if (!userlist.logon(userNameT, passwordT))
				{
					liao_ui[UiType::message] << "User Name already exist!!!";
					if (!JUi::confirm("Do you wish to choose another user name?"))
						break;
				}
				else
				{
					if (currentUser == NULL&&userlist.login(userNameT,passwordT))
					{
						curStage = SHARE_CMD;
						currentUser = userlist.getActive()[0];
					}
					changeDockInfor();
					return true;
				}
			}
		}
		else if (restriction == "o" || restriction == "out")
		{
			userlist.logout(currentUser->getUserName());
			curStage = UNIVER_CMD;
			currentUser = NULL;
			changeDockInfor();
		}
		else
		{
			ui_notice.error();
			ui_notice << "Parameter incorrect";
		}
	}
	else
	{
		ui_notice.error();
		ui_notice << "Infficient paramters for {log}";
	}
	return false;
}
void Center::change(string restriction, vector<string>& parameter)
{
	if (restriction == "ui"||restriction == "userinfor")
	{

	}
	else if (restriction == "ul" || restriction == "userlevel"&&parameter.size()>=3)
	{
		if (currentUser->capable(UserLevel::Administor))
		{
			auto& user = userlist.get(parameter[1]);

		}
		else
			ui_notice[true] << "Invalid operation.";
	}
	else if (restriction == "un" || restriction == "username")
	{

	}
	else if (restriction == "p" || restriction == "password")
	{

	}
}
Center Center::sysCenter;