#pragma once
#include "Elem.h"

//Поиск подходящего курса
struct IsCourse 
{
	int course;

	IsCourse(int _course) 
	{
		course = _course;
	}

	bool operator()(const Elem& e) 
	{
		return e.course == course;
	}
};