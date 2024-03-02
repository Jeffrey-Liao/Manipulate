#include"User.h"
#define USERF "./resource/user.txt"
#pragma region MD5DEF
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

static const char str16[] = "0123456789abcdef";

static const unsigned int T[] = {
    0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
    0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
    0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
    0x6b901122,0xfd987193,0xa679438e,0x49b40821,
    0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
    0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
    0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
    0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
    0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
    0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
    0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
    0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
    0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
    0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
    0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391 };

static const unsigned int s[] = { 7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
                           5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
                           4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
                           6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21 };
class MD5 {
private:
    unsigned int tempA, tempB, tempC, tempD, strlength;
public:
    MD5() {
        tempA = A;
        tempB = B;
        tempC = C;
        tempD = D;
        strlength = 0;
    }
    // F函数
    unsigned int F(unsigned int b, unsigned int c, unsigned int d) {
        return (b & c) | ((~b) & d);
    }
    // G函数
    unsigned int G(unsigned int b, unsigned int c, unsigned int d) {
        return (b & d) | (c & (~d));
    }
    // H函数
    unsigned int H(unsigned int b, unsigned int c, unsigned int d) {
        return b ^ c ^ d;
    }
    // I函数
    unsigned int I(unsigned int b, unsigned int c, unsigned int d) {
        return c ^ (b | (~d));
    }
    // 移位操作函数
    unsigned int shift(unsigned int a, unsigned int n) {
        return (a << n) | (a >> (32 - n));
    }
    // 编码函数
    string encode(string src) {
        vector<unsigned int> rec = padding(src);
        for (unsigned int i = 0; i < strlength / 16; i++) {
            unsigned int num[16];
            for (int j = 0; j < 16; j++) {
                num[j] = rec[i * 16 + j];
            }
            iterateFunc(num, 16);
        }
        return format(tempA) + format(tempB) + format(tempC) + format(tempD);
    }
    // 循环压缩
    void iterateFunc(unsigned int* X, int size = 16) {
        unsigned int a = tempA,
            b = tempB,
            c = tempC,
            d = tempD,
            rec = 0,
            g, k;
        for (int i = 0; i < 64; i++) {
            if (i < 16) {
                // F迭代
                g = F(b, c, d);
                k = i;
            }
            else if (i < 32) {
                // G迭代
                g = G(b, c, d);
                k = (1 + 5 * i) % 16;
            }
            else if (i < 48) {
                // H迭代
                g = H(b, c, d);
                k = (5 + 3 * i) % 16;
            }
            else {
                // I迭代
                g = I(b, c, d);
                k = (7 * i) % 16;
            }
            rec = d;
            d = c;
            c = b;
            b = b + shift(a + g + X[k] + T[i], s[i]);
            a = rec;
        }
        tempA += a;
        tempB += b;
        tempC += c;
        tempD += d;
    }
    // 填充字符串
    vector<unsigned int> padding(string src) {
        // 以512位,64个字节为一组
        unsigned int num = ((src.length() + 8) / 64) + 1;//number of group
        vector<unsigned int> rec(num * 16);
        strlength = num * 16;
        for (unsigned int i = 0; i < src.length(); i++) {
            // 一个unsigned int对应4个字节，保存4个字符信息
            rec[i >> 2] |= (int)(src[i]) << ((i % 4) * 8);
        }
        // 补充1000...000
        rec[src.length() >> 2] |= (0x80 << ((src.length() % 4) * 8));
        // 填充原文长度
        rec[rec.size() - 2] = (src.length() << 3);
        return rec;
    }
    // 整理输出
    string format(unsigned int num) {
        string res = "";
        unsigned int base = 1 << 8;
        for (int i = 0; i < 4; i++) {
            string tmp = "";
            unsigned int b = (num >> (i * 8)) % base & 0xff;
            for (int j = 0; j < 2; j++) {
                tmp = str16[b % 16] + tmp;
                b /= 16;
            }
            res += tmp;
        }
        return res;
    }
};
#pragma endregion
#pragma region USERDEF
User::User()
    :Level(UserLevel::NoAuthority), active(false)
{}
User::User(const User& exist)
{
    strcpy_s(this->userName, USERNAMELEN, exist.userName);
    this->passwordMD5 = exist.passwordMD5;
    Level = exist.Level;
    active = exist.active;
}
User::User(const char* newUserName, const char* newPassword, UserLevel newLevel)
    :Level(newLevel), active(false)
{
    strcpy_s(userName, USERNAMELEN, newUserName);
    string temp = newPassword;
    MD5 en;
    passwordMD5 = en.encode(temp);
}
bool User::operator <(const User& obj)
{
    return this->Level < obj.Level;
}
bool User::operator >(const User& obj)
{
    return this->Level > obj.Level;
}
bool User::operator  == (const User& obj)
{
    return strcmp(this->userName, obj.userName) == 0;
}
char const* User::getUserName()
{
    return this->userName;
}
bool User::capable(UserLevel existLevel)
{
    return this->Level >= existLevel;
}
bool User::log(string& userName, string& password)
{
    MD5 en;
    password = en.encode(password);
    return active = (this->userName == userName && passwordMD5 == password);
}
void User::logout()
{
    this->active = false;
}
void User::registerUser(const char* newUserName, const char* newPassword, UserLevel newLevel)
{
    strcpy_s(userName, USERNAMELEN, newUserName);
    string temp = newPassword;
    MD5 en;
    passwordMD5 = en.encode(temp);
    Level = newLevel;
}
void User::changePassword(string oldPassword,string newPassword)
{
    MD5 en,en2;
    if(passwordMD5 == en.encode(oldPassword))
        this->passwordMD5 =en2.encode(newPassword);
}
bool User::isActive()
{
    return this->active;
}
void User::setLevel(User& admin, UserLevel newLevel)
{
    if (admin.Level == UserLevel::Administor)
        this->Level = newLevel;
}
void User::save(fstream& file)
{
    if (*userName != '\0')
    {
        int temp = (int)this->Level;
        file << userName << " " << passwordMD5 << " " <<  temp << '\n';
    }
}
void User::read(fstream& file)
{
    int temp;
    file >> userName >> passwordMD5 >> temp;
    this->Level = (UserLevel)temp;
    this->active = false;
}
#pragma endregion
#pragma region USERLISTDEF
bool UserList::empty()
{
    return allUser.getSize() == 0;
}
int UserList::size()
{
    return allUser.getSize();
}
vector<User*>& const UserList::getActive()
{
    return activeList;
}
bool UserList::login(string userName, string password)
{
    string tempPassword;
    for (int n = 0; n < allUser.getSize(); ++n)
    {
        tempPassword = password;
        if (allUser[n].log(userName, tempPassword))
        {
            activeList.push_back(&allUser[n]);
            if (activeList.size() > 10)
                activeList.erase(activeList.begin());
            return true;
        }
    }
    return false;
}
bool UserList::logon(string userName, string password)
{
    int index = this->get(userName);
    if (index == -1)
    {
        allUser.append(User(userName.c_str(), password.c_str()));
        return true;
    }
    return false;
}
bool UserList::logout(string userName)
{
    for (int n = 0; n < activeList.size(); ++n)
    {
        if (activeList[n]->getUserName() == userName)
        {
            activeList[n]->logout();
            activeList.erase(activeList.begin() + n);
            return true;
        }
    }
    return false;
}
void UserList::save()
{
    fstream file(USERF, ios::out);
    file << allUser.getSize()-1 << "\n";
    for (int n = 1; n < allUser.getSize(); ++n)
    {
        allUser[n].save(file);
    }
    file.close();
}
void UserList::read()
{
    fstream file(USERF, ios::in);
    ui_message << "Loading user list ";
    int temp = 0;
    allUser.allocate(1);
    allUser[0].registerUser("liao", "787375lrk", UserLevel::Administor);
    file >> temp;
    if (!file.fail())
    {
        int index = 0;
        ui_loading[temp];
        while (!file.eof()&&index !=temp)
        {
            if (temp == 1)
                ui_loading.complete();
            else
                ui_loading << index;
            allUser.allocate(1);
            allUser[allUser.getSize() - 1].read(file);
            index++;
        }
    }else
        ui_message << "Fail!";
    ui_message.end();
    file.close();
}
int UserList::get(string userName)
{
    for (int n = 0; n < allUser.getSize(); ++n)
    {
        if (allUser[n].getUserName() == userName)
        {
            return n;
        }
    }
    return -1;
}
void UserList::removeUser(string userName)
{
    allUser.remove(this->get(userName));
}
void UserList::changeInfor(string userName,string oldPassword,string newPassword,User* admin, UserLevel newLevel)
{
    int index = this->get(userName);
    if (index != -1)
    {
        if (!allUser[index].capable(newLevel) && admin)
            allUser[index].setLevel(*admin, newLevel);
        if (newPassword.size() != 0&&oldPassword.size()!=0)
            allUser[index].changePassword(oldPassword,newPassword);
    }
    else
    {
        UiNoticeMessage::ui_notice.error();
        UiNoticeMessage::ui_notice << "User not exist";
    }
}
#pragma endregion
