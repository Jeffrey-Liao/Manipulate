#include"JCenter.h"
#define CMD_RESERVED 2
Center::Center()
	:currentUser(NULL), currentCmd(NULL),Language(sysLan::English)
{
}
void Center::border()
{
	JUi::borderLine(100);
	ui_message.end();
	ui_message[true];
}
vector<string>& Center::receiveCmd()
{
	JCmdList::cmdlist.clear();
	currentCmd = JInput::liao_input.input(true);
	return JInput::liao_input.getParameter();
}
vector<string>& Center::receiveInput()
{
	JInput::liao_input.input(false);
	return JInput::liao_input.getParameter();
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
			file.open("../resource/helper/helper_en.txt");
		if (file.fail())
			UiNoticeMessage::ui_notice[true] << "Cannot find help file. Please contact developer.";
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
			if (result->cmdType == UNIVER_CMD)
			{
				if (Language == sysLan::Chinese)
					file.open("./resource/helper/universal.txt");
				else
					file.open("./resource/helper/universal_en.txt");
			}
			else if (result->cmdType >= MAIN_CMD && result->cmdType <= SHARE_CMD)
			{
				if (Language == sysLan::Chinese)
					file.open("./resource/helper/share.txt"), file2.open("./resource/helper/main.txt");
				else
					file.open("./resource/helper/share_en.txt"), file2.open("./resource/helper/main_en.txt");
			}
			else if (result->cmdType >= SHARE_CMD && result->cmdType <= TABLE_CMD)
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
bool Center::command(vector<string>& parameters)
{
	if (parameters.size() >= currentCmd->paraNum || currentCmd->paraNum < 0)
	{
		if (parameters.size() ==0)
		{
			for (int n = 0; n < JCmdList::cmdlist.size(); ++n)
			{
				if (JCmdList::cmdlist[n].cmdType <= curStage&& JCmdList::cmdlist[n].cmdType!=HIDDEN)
					cout << ">>>\t" << JCmdList::cmdlist[n].stdCmd << "\n";
			}
			return true;
		}
		else
		{
			string requirement = parameters[0];
			int index = (int)WC Command, para = 0;
			if (requirement == "a" || requirement == "all")
			{
				for (int n = 0; n < JCmdList::cmdlist.size() - CMD_RESERVED; ++n)
					cout << ">>>\t" << JCmdList::cmdlist[n].stdCmd << "\n";
			}
			else if (requirement == "l" || requirement == "ls" || requirement == "list")
			{
				cout << "\t" << "command\tshort\tstage\tnumber of para\n";
				for (int n = 0; n < JCmdList::cmdlist.size() - CMD_RESERVED; ++n)
				{
					if (JCmdList::cmdlist[n].cmdType <= curStage)
					{
						cout << ">>>\t" << JCmdList::cmdlist[n].stdCmd << "\t"
							<< JCmdList::cmdlist[n].shrCmd << "\t"
							<< (int)JCmdList::cmdlist[n].cmdType << "\t"
							<< (int)JCmdList::cmdlist[n].paraNum << "\n";
					}
				}
			}
			else if (requirement == "la" || requirement == "listall")
			{
				cout << "\t" << "command\t\tshort\tstage\tnumber of para\n";
				for (int n = 0; n < JCmdList::cmdlist.size() - CMD_RESERVED; ++n)
				{
					cout << ">>>\t" << JCmdList::cmdlist[n].stdCmd << "\t\t"
						<< JCmdList::cmdlist[n].shrCmd << "\t"
						<< (int)JCmdList::cmdlist[n].cmdType << "\t"
						<< (int)JCmdList::cmdlist[n].paraNum << "\n";
				}
			}
			else if (requirement == "u" || requirement == "universal")
			{
				for (int n = 0; n < JCmdList::cmdlist.size() - CMD_RESERVED; ++n)
				{
					if (JCmdList::cmdlist[n].cmdType == UNIVER_CMD)
						cout << ">>>\t" << JCmdList::cmdlist[n].stdCmd << "\n";
				}
			}
			else if (requirement == "m" || requirement == "main")
			{
				for (int n = 0; n < JCmdList::cmdlist.size() - CMD_RESERVED; ++n)
				{
					if (JCmdList::cmdlist[n].cmdType >= MAIN_CMD && JCmdList::cmdlist[n].cmdType <= SHARE_CMD)
						cout << ">>>\t" << JCmdList::cmdlist[n].stdCmd << "\n";
				}
			}
			else if (requirement == "t" || requirement == "table")
			{
				for (int n = 0; n < JCmdList::cmdlist.size() - CMD_RESERVED; ++n)
				{
					if (JCmdList::cmdlist[n].cmdType >= SHARE_CMD)
						cout << ">>>\t" << JCmdList::cmdlist[n].stdCmd << "\n";
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
		UiNoticeMessage::ui_notice.error();
		UiNoticeMessage::ui_notice << "Insufficient parameters for {command}";
	}
}
void Center::execute()
{
	userlist.read();
	if (userlist.empty())
	{
		UiDock::ui_dock << "Help";
		ui_message << "Try to type 'help' command in the terminal, if you are new user\n";
		ui_message.end();
	}
	UiDock::ui_dock << "No user Login";
	while (1)
	{
		try
		{
			auto parameter = receiveCmd();
			if (currentCmd != NULL && currentCmd->word != WordCmd::Quit)
			{
				if (currentCmd->word == WordCmd::Help)
					help(parameter);
				else if (currentCmd->word == WordCmd::Command)
					command(parameter);
				else if (currentCmd->word == WordCmd::Version)
					version();
				else if (currentCmd->word == WordCmd::Exist)
					exist(parameter);
				else if (currentCmd->word == WordCmd::Log)
					login(parameter);
				border();
			}
			else
			{
				if (JUi::confirm("Exit the system?"))
				{
					userlist.save();
					break;
				}
				currentCmd = NULL;
				UiDock::ui_dock.call();
			}
		}
		catch (LiaoException* fatalError)
		{
			cout << "\n" << fatalError->getErrorMessage();
			delete fatalError;
			system("pause");
			UiDock::ui_dock.call();
		}
		catch (LiaoException fatalError)
		{
			cout << "\n" << fatalError.getErrorMessage();
			system("pause");
			UiDock::ui_dock.call();
		}
	}
}
void Center::version()
{
	char temp[500];
	ifstream file("./resource/versionInf.txt");
	if (file.fail())
		throw new LiaoException("Center", "version", "Target file missing");
	while (!file.eof())
	{
		file.getline(temp, 500);
		cout << temp << "\n";
	}
	file.close();
}
bool Center::exist(vector<string>& parameter)
{
	if (parameter.size() >= currentCmd->paraNum)
	{
		string restriction = parameter[0];
		if (restriction == "c" || restriction == "command")
		{
			if (JCmdList::cmdlist.get(parameter[1]) != NULL)
				ui_message << "Command Exist\n";
			else
				ui_message << "Command Not Exist\n";
			return JCmdList::cmdlist.get(parameter[1]) != NULL;
		}
		else if (restriction == "u" || restriction == "user")
		{
			bool result = userlist.get(parameter[1]) != -1;
			if (result)
				ui_message << "User exist";
			else
				ui_message << "User not exist";
			ui_message.end();
			return result;
		}
		else if (restriction == "t" || restriction == "table")
			cout << "Coming soon\n";
		return true;
	}
	else
	{
		UiNoticeMessage::ui_notice.error();
		UiNoticeMessage::ui_notice << "Insufficient parameters for {exist}";
		return false;
	}
}
bool Center::logInterface(string& userNameT, string& passwordT)
{
	ui_message << "Please give your user name:";
	if (JInput::liao_input.input(false) == NULL && !JInput::liao_input.paraEmpty())
	{
		userNameT = JInput::liao_input.getParameter()[0];
		ui_message << "Please give your password:";
		if (JInput::liao_input.input(false) == NULL && !JInput::liao_input.paraEmpty())
		{
			passwordT = JInput::liao_input.getParameter()[0];
		}
		else
		{
			ui_message.end();
			return false;
		}
	}
	else
	{
		ui_message.end();
		return false;
	}
	return true;
}
void Center::changeDockInfor()
{
	if (currentUser != NULL)
		UiDock::ui_dock.change( currentUser->getUserName());
	else
		UiDock::ui_dock.change("No user Login");
}
bool Center::login(vector<string>& parameter)
{
	if (parameter.size() >= currentCmd->paraNum)
	{
		string restriction = parameter[0];
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
					ui_message << "User name or password incorrect";
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
					ui_message << "User Name already exist!!!";
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
			UiNoticeMessage::ui_notice.error();
			UiNoticeMessage::ui_notice << "Parameter incorrect";
		}
	}
	else
	{
		UiNoticeMessage::ui_notice.error();
		UiNoticeMessage::ui_notice << "Infficient paramters for {log}";
	}
	return false;
}
Center Center::sysCenter;