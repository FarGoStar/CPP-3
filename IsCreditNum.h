#pragma once
#include "Elem.h"

//Поиск подходящего номера зачетной книжки
struct IsCreditNum
{

	int  creditNum;

	IsCreditNum(int _creditNum)
	{
		creditNum = _creditNum;
	}

	bool operator()(const Elem& e)
	{
		return e.creditNum == creditNum;
	}
};
