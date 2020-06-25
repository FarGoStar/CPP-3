#pragma once
#include <string>
#include "Elem.h"

//Поиск подходящей дисциплины
struct IsDisc
{

	string  disc;

	IsDisc(string _disc)
	{
		disc = _disc;
	}

	bool operator()(const Elem& e)
	{
		for (int i=0; i<5; i++)
			if (e.disc[i] == disc) return true;
		return false;
	}
};