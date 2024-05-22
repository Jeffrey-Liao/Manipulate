#pragma once
#ifndef USER_H
#define USER_H
#include "../CommonDefines/Defines.h"
#include "../DataUnit/LinkList.h"
namespace liao
{
	enum class UserLevel
	{
		NoAuthority,
		Guest,
		Visitor,
		SuperVisitor,
		Operator,
		SuperOperator,
		Administor,
		Super
	};
	//用户信息类
	class User
	{
		//用户名称
		char userName[USERNAMELEN] = { '\0' };
		//用户密码（MD5格式）
		string passwordMD5;
		//用户级别
		UserLevel Level;
		//用户是否在线
		bool active;
	private:
		//对用户名称，用户密码，用户级别进行覆写
		void registerUser(const char* newUserName, const char* newPassword, UserLevel newLevel);
	protected:
		User();
		//拷贝构造函数
		User(const User& exist);
		//根据用户名称，密码，用户级别（可选）新建用户
		User(const char* newUserName, const char* newPassword, UserLevel newLevel);
		virtual void resetLevel() = 0;
	public:
		//获取用户名称（c_str）
		char const* getUserName();
		//用户权限许可测试
		bool capable(UserLevel existLevel);
		//登录接口，active设为true
		bool log(string& userName, string& password);
		//登出接口，active设为false
		void logout();
		//更改用户级别
		void setLevel(User& admin, string newLevel);
		//更改用户级别
		void setLevel(User& admin, UserLevel newLevel);
		//查看用户登录情况
		bool isActive();
		//修改密码
		void changePassword(string oldPassword, string newPassword);
		//保存用户信息到指定文件
		void save(fstream& file);
		//从指定文件读取用户信息
		void read(fstream& file);
		//比较用户间级别
		bool operator <(const User& obj);
		//比较用户间级别
		bool operator >(const User& obj);
		//比较用户间级别
		bool operator  == (const User& obj);
		virtual void promote(const User& executor)=0;
		
		static string Level2Str(UserLevel userLevel)
		{
			if (userLevel == UserLevel::Guest)
				return "guest";
			else if (userLevel == UserLevel::NoAuthority)
				return "no authority";
			else if (userLevel == UserLevel::Administor)
				return "administor";
			else if (userLevel == UserLevel::Visitor)
				return "user";
			else if (userLevel == UserLevel::Operator)
				return "operator";
			else if (userLevel == UserLevel::Super)
				return "super";
			else if (userLevel == UserLevel::SuperVisitor)
				return "super user";
			else if (userLevel == UserLevel::SuperOperator)
				return "super operator";
			else
				return "error";
		}
	};
	class Guest:public User
	{
	public:
		Guest(const char* newUserName, const char* newPassword);
		Guest(const Guest& obj);
		void promote(const User& executor);
	};
	class Visitor:public User
	{
	public:
		Visitor(const char* newUserName, const char* newPassword);
		Visitor(const Visitor& obj);
		void promote();
	};
	class Operator :public User
	{
	public:
		Operator(const char* newUserName, const char* newPassword);
		Operator(const Operator& obj);
		void promote(const User& executor);
	};
	class Administrator :public User
	{
	public:
		Administrator(const char* newUserName, const char* newPassword);
		Administrator(const Administrator& obj);
		void promote(const User& executor);
	};
	class Super :public User
	{
	public:
		Super(const char* newUserName, const char* newPassword);
		Super(const Super& obj);
	};
	class UserList
	{
		LinkList<User> allUser;
		vector<User*> activeList;
	public:
		bool empty();
		vector<User*>& const getActive();
		int size();
		User& get(string userName);
		int getIndex(string userName);
		bool login(string userName, string password);
		bool logon(string userName, string password);
		bool logout(string userName);
		void removeUser(string userName);
		void changeInfor(string userName, string oldPassword, string newPassword, User* admin = NULL, UserLevel newLevel = UserLevel::Guest);
		void save();
		void read();
	};
}

#endif