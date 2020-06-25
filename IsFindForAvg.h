#pragma once
#include <string>
#include "Elem.h"

//Поиск подходящей записи по курсу, номеру группы и дисциплине для нахождения среднего балла
struct IsAvgMinMax {
	int min;
	int max;
	IsAvgMinMax(int _max, int _min)
	{
		min = _min;
		max = _max;
	}
	bool operator()(const Elem& e)
	{
		double sum = 0;
		for (int i = 0; i < 5; i++)
		{ 
			sum += e.marks[i]; 
		};
		if (((sum / 5) < max) && ((sum / 5) > min)) return true;
		else return false;
	};
};