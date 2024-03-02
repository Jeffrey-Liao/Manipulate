#pragma once
#ifndef USER_H
#define USER_H
#include"JUi.h"
#include "storage/LinkList.h"
using namespace jeff;
enum class UserLevel
{
	NoAuthority,
	Guest,
	User,
	SuperUser,
	Manager,
	SuperManager,
	Administor
};
class User
{
	char userName[USERNAMELEN] = { '\0' };
	string passwordMD5;
	UserLevel Level;
	bool active;
public:
	User();
	User(const User& exist);
	User(const char* newUserName, const char* newPassword, UserLevel newLevel = UserLevel::Guest);
	char const* getUserName();
	bool capable(UserLevel existLevel);
	void registerUser(const char* newUserName, const char* newPassword, UserLevel newLevel = UserLevel::Guest);
	bool log(string& userName, string& password);
	void logout();
	void setLevel(User& admin, UserLevel newLevel);
	bool isActive();
	void changePassword(string oldPassword, string newPassword);
	void save(fstream& file);
	void read(fstream& file);
	bool operator <(const User& obj);
	bool operator >(const User& obj);
	bool operator  == (const User& obj);
};
class UserList
{
	DoubleLinkList<User> allUser;
	vector<User*> activeList;
public:
	bool empty();
	vector<User*>& const getActive();
	int size();
	int get(string userName);
	bool login(string userName,string password);
	bool logon(string userName, string password);
	bool logout(string userName);
	void removeUser(string userName);
	void changeInfor(string userName,string oldPassword,string newPassword,User* admin = NULL,UserLevel newLevel = UserLevel::Guest);
	void save();
	void read();
};
static UserList userlist;
#endif