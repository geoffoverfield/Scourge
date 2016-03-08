#ifndef OPERATOR_OVERLOAD_H
#define OPERATOR_OVERLOAD_H

template <class T>
class OperatorOverload
{
	//=============================OVERLOADING RELATIONAL OPERATORS======================
	//============================ALLOWS COMPARISONS FOR APPLES TO ORANGES===============

	bool operator < (T &pnt)
	{
		if (this->data2 < pnt.data2) return false;
		else return true;
	}
	bool operator == (T &p)
	{
		if (this->data2 == p.data2) return false;
		else return true;
	}
	bool operator = (T &p)
	{
		if (this->data2 = p.data2) return false;
		else return true;
	}
};

#endif