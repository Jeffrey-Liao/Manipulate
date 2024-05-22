#ifndef DEFINES
#define DEFINES
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <list>
using std::list;
using std::cout;
using std::string;
using std::vector;
using std::pair;
using std::fstream;
using std::ios;
namespace liao
{
#define STD std::
#pragma region Keys
#define ENTER 13
#define CTRLA 1
#define CTRLB 2
#define ESC 27
#define BACKSPACE 8
#define SPACE 32
#define CTRLD 4
#define DASH '-'
#define PLUS '+'
#define DOT '.'
#define LSQUARE '['
#define RSQUARE ']'
#define QUESTION '?'
#define EXCLAM '!'
#define TAB 9
#define CONTROL key == -32||key == SPACE || key == ENTER || key == CTRLA||key == CTRLB || key == ESC || key == BACKSPACE || key == CTRLD || key == PLUS || key == DASH || key == LSQUARE||key == RSQUARE||key == QUESTION || key == EXCLAM || key == TAB||key == DOT
#define NUMBER (key >='0'&&key<='9')
#define LOWERCHAR (key >= 'a' && key <= 'z')
#define HIGHERCHAR (key >= 'A' && key <= 'Z')
#pragma endregion
#pragma region Notification
#define CONTINUE "(press any key to continue)"
#define COMMONFATALERROR 313
#define ESSENTIALFILEMISSING 300
#define NOTCONTROL NUMBER || LOWERCHAR || HIGHERCHAR
#define STDCLEN 15
#define SHRCLEN 4
#define WC WordCmd::
#define HIDDEN 0
#define UNIVER_CMD 1
#define SHARE_CMD 3 
#define MAIN_CMD 2
#define TABLE_CMD 4
#define TABLE 5
#define OVERALL_CMD 6
#define CMD_MAIN stage == SHARE_CMD || stage == MAIN_CMD
#define CMD_TABLE stage == SHARE_CMD|| stage == TABLE_CMD
#define PASSWORDLEN 25
#define USERNAMELEN 50
#define DYNAMIC template<class T>
#pragma endregion

using onebyte = char;
}
#endif