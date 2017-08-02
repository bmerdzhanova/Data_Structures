#include "Operator.h"

Operator::Operator():op('\0'),symbol('\0'),associative(0), priority(0)
{
	/*...*/
}

Operator::Operator(char newSym, char newOp, bool newAssoc, int newPriority)
{
	symbol = newSym;
	op = newOp;
	associative = newAssoc;
	priority = newPriority;
}

Operator::Operator(const Operator & other)
{
	copy(other);
}

Operator & Operator::operator=(const Operator & other)
{
	if (this != &other)
	{
		copy(other);
	}
	return *this;
}

Operator::~Operator()
{

}

char Operator::getSymbol() const
{
	return symbol;
}

char Operator::getOp() const
{
	return op;
}

void Operator::copy(const Operator & other)
{
	op = other.op;
	symbol = other.symbol;
	associative = other.associative;
	priority = other.priority;
}
