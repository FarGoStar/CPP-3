#pragma once
#include <string>
#include "Elem.h"

//Поиск подходящей фамилии студента
struct IsSurname
{

	string  surname;

	IsSurname(string _surname)
	{
		surname = _surname;
	}

	bool operator()(const Elem& e)
	{
		return e.surname == surname;
	}
};
