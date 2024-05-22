#pragma once
#pragma once
#ifndef MACRO_H
#define MACRO_H
#include <cstdlib>
#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <conio.h>
#define PASSWORDLEN 25
#define USERNAMELEN 50
#define CONTINUE "(press any key to continue)"
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
#define DYNAMIC template<class T>
#define INT4NAME typeid(int).name()
#define INT2NAME typeid(short int).name()
#define INT1NAME typeid(onebyte).name()
#define INT8NAME typeid(long long).name()
#define CHARNAME typeid(char).name()
#define FLOATNAME typeid(float).name()
#define DOUBLENAME typeid(double).name()
#define STRINGNAME typeid(std::string).name()
#define BOOLNAME typeid(bool).name()
#define CONFIRM key == 'y' || key == 'Y'||key == 13
#define DENY key == 'n' || key == 'N' || key == 27
//Keys

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
#define DEBUGF "./log/debug.log"
#define ERRORF "./log/error.log"
using onebyte = char;
using namespace std;
#endif