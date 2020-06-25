#pragma once
#include <string>
#include "Elem.h"

//Поиск подходящей записи
struct IsFindStudentInfo {
	int course;
	int group;
	string surname;
	int creditNum;
	IsFindStudentInfo(int _course, int _group, string _surname,
		int _creditNum)
	{
		course = _course;
		group = _group;
		surname = _surname;
		creditNum = _creditNum;
	}
	bool operator()(const Elem& e)
	{
		return (course == e.course)
			&& (group == e.group)
			&& (surname == e.surname)
			&& (creditNum == e.creditNum);
	}
};