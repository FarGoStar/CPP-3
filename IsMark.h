#pragma once
#include "Elem.h"

//Поиск подходящей оценки
struct IsExcellentMark
{

	int  mark;

	bool operator()(const Elem& e)
	{
		for (int i = 0; i < 5; i++)
			if (e.marks[i] != 5) return false;
		return true;
	}
};