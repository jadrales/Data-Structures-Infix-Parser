#include "Token.h"
#include <string>
#include <algorithm>
using namespace std;


Token::Token(int inopd)
{
	opd = inopd;
	opr = "";
}

Token::Token(string inopr)
{
	opr = inopr;
	opd = NULL;
}

int Token::getopd()
{

	return opd;
}

void Token::setopd(int inopd)
{
	opd = inopd;
}

void Token::setopr(string inopr)
{
	opr = inopr;
}

void Token::setanswer(int answer)
{
	//return answer;
}

bool Token::isopd()
{
	if (opd != NULL)
	{
		return true;
	}

	return false;
}

bool Token::isopr()
{
	if (opr.length() != 0) {
		return true;
	}
	return false;
}

bool Token::is_binary()
{
	vector<string>::iterator it;
	it = find(binary.begin(), binary.end(), opr);
	if (it != binary.end())
		
		return true;
	else
		return false;
	
}


bool Token::is_unary()
{
	vector<string>::iterator it;
	it = find(unary.begin(), unary.end(), opr);
	if (it != unary.end())
		return true;
	else
		return false;
}

char Token::get_type()
{
	if (is_binary)
	{
		return 'B';
	}
	if (is_unary)
	{
		return 'U';
	}
}

char Token::multiply()
{
	char mult = '*';
	return mult;
}

//This is a test.
