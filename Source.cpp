#include <iostream>
#include <stack>
#include <string>

using namespace std;


// We call this in the main function
double eval(string _input) {
	stack<double> numberStack;
	stack<char> operatorStack;
	int numberArray[10] = { 0,1,2,3,4,5,6,7,8,9 };
	char operatorArray[7] = { '^', '(', ')', '*','/','+','-' };

	if (_input.size() != 0) //If character exists to be read
	{
		for (i = 0; i < _input.size(); i++) // (1)If character is operand push on the operand stack, if character is (, push on the operator stack.
		{
			for (j = 0; j < 10; j++)
			{
				if (j == i) // Character is a number
				{
					numberStack.push(i);
				}
			}
			for (int k = 0; k < 7; k++)
			{
				if (k == i) // (2)Else if character is operator
				{
					if (i == '(')
					{
						operatorStack.push(i);
					}


					else if (operatorStack.top() !< i)// (2.1) While the top of the operator stack is not of smaller precedence than this character.
					{
					label:
						operatorStack.pop(); // (2.2) Pop operator from operator stack.
						int oper1 = numberStack.pop(); // (2.3) Pop two operands (oper1 and oper2) from operand stack.
						int oper2 = numberStack.pop(); // (2.4) Store oper1 and oper2 on the operand stack back to (2.1).
					}

					else if (i == ')')
					{
						goto label; // (3) Else if character is ')', do the same as 2.2 - 2.4 till you encounter '('.
					}
				}
			}
		}








	}
	for (int l = 0; l < operatorStack.size(); l++) //No more character left to read
	{
		operatorStack.pop(); //Pop operators untill operator stack is ?not? empty.
	}

	numberStack.pop(); //Pop top 2 operands and push op1 op op2 on the operand stack.
	numberStack.pop();
	return numberStack.top();//Return the top value from operand stack.
}

// Main
int main() {

	double result = eval("!!!3+2");
	cout << result;
	return 0;

}