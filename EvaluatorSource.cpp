#include "Evaluator.h"
#include "Syntax_Error.h"
#include "Infix_Parser.h"
#include "Token.h"
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;





void Evaluator::setTokens(vector<Token> _v)
{
	
}

int Evaluator::getPrecedence(string _operator)
{
	if (_operator == "^")
	{
		return precedence = 7;
	}
	else if (_operator == "*")
	{
		return precedence = 7;
	}
	else if (_operator == "/")
	{
		return precedence = 7;
	}
	else if (_operator == "%")
	{
		return precedence = 7;
	}
	else if (_operator == "+")
	{
		return precedence = 5;
	}
	else if (_operator == "-")
	{
		return precedence = 5;
	}
	else if (_operator == "<")
	{
		return precedence = 4;
	}
	else if (_operator == "<=")
	{
		return precedence = 4;
	}

	else if (_operator == ">")
	{
		return precedence = 4;
	}
	else if (_operator == ">=")
	{
		return precedence = 4;
	}
	else if (_operator == "!=")
	{
		return precedence = 3;
	}
	else if (_operator == "==")
	{
		return precedence= 3;
	}
	else if (_operator == "&&")
	{
		return precedence = 2;
	}
	else if (_operator == "||")
	{
		return precedence = 1;
	}
	else
	{
		Syntax_Error("Invalid operator!");
	}
}

Evaluator::Evaluator()
{

}



Token Evaluator::calculateUnary(Token _operator, Token _right)
{
	
	Token answer = 0;
	if (_operator.getopr() == "++")
	{
		answer.setopd(_right.getopd() + 1);
	}
	else if (_operator.getopr() == "--")
	{
		answer.setopd(_right.getopd() - 1);
	}
	else if (_operator.getopr() == "-")
	{
		answer.setopd(-_right.getopd());
	}
	else if (_operator.getopr() == "!")
	{
		answer.setopd(!_right.getopd());
	}
	else
	{
		Syntax_Error("Invalid operator!");
	}
	return answer;
}

Token Evaluator::calculateBinary(Token _left, Token _operator, Token _right)
{
	Token answer = 0;
	
	if (_operator.getopr() == "^")
	{
		answer.setopd(pow(_left.getopd(), _right.getopd()));
	}

	else if (_operator.getopr() == "*")
	{
		answer.setopd(_left.getopd() * _right.getopd());
	}

	else if (_operator.getopr() == "/")
	{
		answer.setopd(_left.getopd() / _right.getopd());
	}

	else if (_operator.getopr() == "+")
	{
		answer.setopd(_left.getopd() + _right.getopd());
	}

	else if (_operator.getopr() == "-")
	{
		answer.setopd(_left.getopd() - _right.getopd());
	}

	else if (_operator.getopr() == "<")
	{
		answer.setopd(_left.getopd() < _right.getopd());
	}

	else if (_operator.getopr() == "<=")
	{
		answer.setopd(_left.getopd() <= _right.getopd());
	}

	else if (_operator.getopr() == ">")
	{
		answer.setopd(_left.getopd() > _right.getopd());
	}

	else if (_operator.getopr() == ">=")
	{
		answer.setopd(_left.getopd() >= _right.getopd());
	}

	else if (_operator.getopr() == "%")
	{
		answer.setopd(_left.getopd() % _right.getopd());
	}

	else if (_operator.getopr() == "==")
	{
		answer.setopd(_left.getopd() == _right.getopd());
	}

	else if (_operator.getopr() == "!=")
	{
		answer.setopd(_left.getopd() != _right.getopd());
	}

	else if (_operator.getopr() == "&&")
	{
		answer.setopd(_left.getopd() && _right.getopd());
	}

	else if (_operator.getopr() == "||")
	{
		answer.setopd(_left.getopd() || _right.getopd());
	}

	else
	{
		Syntax_Error("Invalid argument!");
	}
	
	return answer;
}

int Evaluator::evaluate()
{
	Token getopr(), get_type(), getopd();
	int index = 0;

	// Error detection
	if (v[0].getopr() == ")")
	{
		cout << "Cannot begin with a ) character! " << index << endl;
		exit(0);
	}

	else if (v[0].getopr() != "" && v[0].get_type() == 'B')
	{
		cout << "Cannot begin with binary character! " << index << endl;
		exit(0);
	}

	for (std::vector<Token>::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		std::vector<Token>::iterator nextCharacter = iter;
		nextCharacter++;
		if (iter->getopr() == "/" && nextCharacter->getopr() == "" && nextCharacter->getopd() == 0)
		{
			cout << "You cannot divide by zero! " << index << endl;
			exit(0);
		}

		// If the character is an operand then push to the operand stack
		if (iter->getopr() == "" && !lastOperand)
		{
			operandStack.push(*iter);
			lastOperand = true;

			while (!operatorStack.empty())
			{
				if (operatorStack.empty() || operandStack.empty())
				{
					cout << "Either the operator stack is empty or the operand stack is empty" << index << endl;
					exit(0);
				}
				// If the top of the operator stack has a unary operator than continue to calculate unary operators
				if (operatorStack.top().get_type() == 'U')
				{
					Token center(), right();
					center() = operatorStack.top(); //Added a () and the l,r,c in token.h
					operatorStack.pop();
					right() = operandStack.top();
					operandStack.pop();
					operandStack.push(calculateUnary(center(), right()));
				}
				else
				{
					break;
				}
			}
		}
		// Error checking to see if there are two operands
		else if (iter->getopr() == "" && lastOperand)
		{
			cout << "There cannot be two operands back to back. " << index << endl;
			exit(0);
		}
		else if (iter->getopr() == "(")
		{
			// If the previous number was an operand then multiply
			if (lastOperand)
			{
				Token::multiply;
				multiply.setopr("*"); //Not sure if this will wor
				operatorStack.push('*');
			}
			operatorStack.push(*iter);
			lastOperand = false;
		}
		else if (iter->getopr() != "" && lastOperand && iter->get_type() == 'B')
		{
			if (operatorStack.empty())
			{
				operatorStack.push(*iter);
				lastOperand = false;
			}

			//The check the precedence of current token compared to the top of the operatorStack
			else if (getPrecedence(iter->getopr()) > getPrecedence(operatorStack.top().getopr()))
			{
				operatorStack.push(*iter);
				lastOperand = false;
			}
			else if (getPrecedence(iter->getopr()) <= getPrecedence(operatorStack.top().getopr()))
			{
				// If the top of the operator stack has precedence over or equal to then calculateBinary
				if (operatorStack.empty() || operandStack.empty())
				{
					cout << "At least one of the stacks are empty. " << index << endl;
					exit(0);
				}
				Token left(), center(), right();
				right() = operandStack.top();
				operandStack.pop();
				left() = operandStack.top();
				operandStack.pop();
				center() = operatorStack.top();
				operatorStack.pop();
				operandStack.push(calculateBinary(left(), center(), right()));
				operatorStack.push(*iter);
				lastOperand = false;
			}
		}

		else if (iter->getopr() != "" && !lastOperand && iter->get_type() == 'B')
		{
			cout << "You cannot have two binary operators back to back. " << index << endl;
			exit(0);
		}

		// Push the unarys from operatorStack
		else if (iter->getopr() != "" && iter->get_type() == 'U')
		{
			if (nextCharacter != v.end())
			{
				// If it's binary
				if (nextCharacter->getopr() != "" && nextCharacter->get_type() == 'B')
				{
					cout << "There cannot be a unary then binary operator back to back. " << index << endl;
					exit(0);
				}
				//If it's unary, push it to the operator stack
				else if (nextCharacter->getopr() != "" && nextCharacter->get_type() == 'U')
				{
					operatorStack.push(*iter);
				}
				else if (nextCharacter->getopr() == "")
				{
					operatorStack.push(*iter);
				}
				else
				{
					cout << "A number or a unary operator did now come after a unary operator. " << index << endl;
					exit(0);
				}
			}
		}
		// If precedence dominates then calculate until ')' is found.
		else if (iter->getopr() == ")") {
			while (!operatorStack.empty())
			{
				if (operatorStack.empty())
				{
					cout << "There was no ')' found. The stack is empty. " << index << endl;
					exit(0);
				}
				if (operatorStack.top().getopr() != "(")
				{
					Token left(), center(), right();
					right() = operandStack.top();
					operandStack.pop();
					left() = operandStack.top();
					operandStack.pop();
					center() = operatorStack.top();
					operatorStack.pop();
					operandStack.push(calculateBinary(left(), center(), right()));
				}
				else
				{
					break;
				}
			}
			operatorStack.pop();
			lastOperand = true;

		}
		index += 1;
	}
	// Calculate until only one is left in the operand stack
	while (!operatorStack.empty())
	{
		Token left(), center(), right();
		right() = operandStack.top();
		operandStack.pop();
		left() = operandStack.top();
		operandStack.pop();
		center() = operatorStack.top();
		operatorStack.pop();

		operandStack.push(calculateBinary(left(), center(), right()));
	}
	int result = operandStack.top().getopd();
	operandStack.pop();

	//This checks to see if something messed up
	if (!operandStack.empty())
	{
		cout << "The operand stack is not empty." << index << endl;
		exit(0);
	}
	return result;
}

int main()
{
	/*string y = "3 + 5";
	Infix_Parser parser;
	string result = parser.parse(y);
	return 0;*/
}