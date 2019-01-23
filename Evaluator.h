#ifndef EVALUATOR_H_
#define EVALUATOR_H_
#include "Syntax_Error.h"
#include "Infix_Parser.h"
#include "Token.h"
#include <string>
#include <stack> 
using namespace std;

//Evaluator parser;
//string result = parser.convert();

class Evaluator {
public:

	// string convert(const std::string& expression);

//	void process_operator(char op);
	
	

	stack<Token> operandStack;
	stack<Token> operatorStack;
	vector<Token> v;
	bool lastOperand = false;

private:
	// Constructors
	//Evaluator() {}; //calculateUnary won't work as long constructor is active
	Evaluator(vector<Token> input) { v = input; };

	string tokens;
	vector<Token> getTokens() { return v; };
	void setTokens(vector<Token> _v);
	string postfix;
	int getPrecedence(string _operator);

	Evaluator();

	int evaluate();

	Token calculateUnary(Token _operator, Token _right);
	Token calculateBinary(Token _left, Token _operator, Token _right);

	
	
	int precedence;
};

#endif


