#include <iostream>
#include <fstream>
#include <iomanip>
#include "DynamicArray.h"
#include "LinkedStack.h"
#include "Operator.h"

double calculate(char op, double left, double right, DynamicArray<Operator> operators)
{
	for (int i = 0; i < operators.getSize(); i++)
		if (operators[i].getSymbol() == op)
			op = operators[i].getOp();

	switch (op) {
	case '+': return  left + right;
	case '-': return  left - right;
	case '*': return left * right;
	case '/': return left / right;
	}
}

double sum(char* expression, DynamicArray<Operator> operators)
{
	LinkedStack<double> op;
	for (int i = 0; i < strlen(expression); i++)
	{
		char* cur = new char[strlen(expression) + 1];
		int j = 0;
		if (expression[i] >= '0' && expression[i] <= '9' || expression[i] == '-' && expression[i + 1] >= '0' && expression[i + 1] <= '9')
		{
			if (expression[i] == '-')
			{
				cur[j] = expression[i];
				i++; j++;
			}

			while (expression[i] >= '0' && expression[i] <= '9')
			{
				cur[j] = expression[i];
				j++; i++;
			}
			cur[j] = '\0';
			op.push(atof(cur));
		}
		else if (expression[i] < '0' || expression[i] > '9')
		{
			if (op.getSize() < 2)
				return -1;

			double right = op.peek();
			op.pop();
			double left = op.peek();
			op.pop();

			op.push(calculate(expression[i], left, right, operators));
			i++;
		}
	}

	return op.peek();
}

int getPriority(char op)
{
	if (op == '+' || op == '-')
		return 0;
	else if(op == '*' || op == '/')
		return 1;

	return -1; //error
}

//function for reading the operators from text file
void readOperators(char* fileName, DynamicArray<Operator>& operators)
{
	std::ifstream file(fileName);

	if (file)
	{
		while (!file.eof())
		{
			char newOp, newSym;
			bool newAssoc;
			int newPriority;
			file >> newSym >> newOp >> newAssoc;
			newPriority = getPriority(newOp);
			Operator newOperator(newSym, newOp, newAssoc, newPriority);
			operators.pushBack(newOperator);
		}
	}

	file.close();
}

bool isOperator(char op, DynamicArray<Operator> operators)
{
	for (int i = 0; i < operators.getSize(); i++)
		if (operators[i].getSymbol() == op)
			return true;

	return false;
}

void readExpression(LinkedStack<char*>& expression, char* fileName)
{
	std::ifstream file(fileName);
	if (file)
	{
		while (!file.eof())
		{
			char* cur = new char[1024];

			file >> cur;
			expression.push(cur);
		}
	}

	file.close();
}

int getExprLen(char* fileName)
{
	std::ifstream file(fileName);

	if (file)
		file.seekg(0, std::ios::end);

	int len = file.tellg();
	file.close();
	return len;
}

char* prefixToPostfix(LinkedStack<char*>& expression, DynamicArray<Operator> op)
{
	LinkedStack<char*> operands;

	while (!expression.isEmpty())
	{
		char* cur = new char[1024];
		
		cur = expression.peek();
		if (strlen(cur) == 1 && *cur >= '0' && *cur <= '9' || strlen(cur) != 1)
		{
			operands.push(cur);
			expression.pop();
		}
		else
		{
			if (operands.getSize() >= 2)
			{
				double opSize = operands.getSize();
				char* first = new char[strlen(operands.peek()) + 2];
				strcpy(first, operands.peek());
				strcat(first, " ");
				operands.pop();

				char* second = new char[strlen(operands.peek()) + 2];
				strcpy(second, operands.peek());
				strcat(second, " ");
				operands.pop();

				char* newOperand = new char[strlen(first) + strlen(second) + 2];
				strcpy(newOperand, first);
				strcat(newOperand, second);
				strcat(newOperand, cur);
				operands.push(newOperand);
				expression.pop();

				delete[] first;
				delete[] second;
			}

			delete[] cur;
		}

	}
	return operands.peek();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Error!" << std::endl;
		return 1;
	}

	DynamicArray<Operator> operators;
	readOperators(argv[2], operators);

	LinkedStack<char*> expression;
	readExpression(expression, argv[1]);

	char* expr = new char[getExprLen(argv[1])+1];
	expr = prefixToPostfix(expression, operators);

	double sumExpr = 0;
	sumExpr = sum(expr, operators);

	std::cout << expr << std::endl;
	std::cout << std::fixed;
	std::cout << std::setprecision(5) << sumExpr << std::endl;
	return 0;
}