#ifndef OPERATOR_HEADER_INCLUDED
#define OPERATOR_HEADER_INCLUDED

class Operator
{
public:
	Operator();
	Operator(char, char, bool, int);
	Operator(const Operator&);
	Operator& operator=(const Operator&);
	~Operator();

	char getSymbol() const;
	char getOp() const;
private:
	void copy(const Operator&);

private:
		char op;
		char symbol;
		bool associative;
		int priority;
};

#endif //OPERATOR_HEADER_INCLUDED