#pragma once
#include "StudentInfoList.h"
#include <string>
#include <fstream>
#include <algorithm>
#include "IsFindStudentInfo.h"

using namespace std;
class MyDeanery
{
	StudentInfoList student;
	const string FILENAME = "Deanery.bin";
	deque<Elem>::iterator x;

public:
	void Serialize() 
	{
		ofstream ofs(FILENAME, ios::binary | ios::out);
		student.Serialize(ofs);
		ofs.close();
	}

	void Deserialize() 
	{
		ifstream ifs(FILENAME, ios::binary | ios::in);
		student.Deserialize(ifs);
		ifs.close();
	};

	void AddStudent()
	{
		student.AddStudentInfo();
	}
	void DeleteStudent(int Credit)
	{
		x = find_if(student.deq.begin(), student.deq.end(), IsCreditNum(Credit));
		student.PrintInfo(x);
		student.DeleteStudentInfo(x);
	}
	void ChangeStudentInfo(int Credit)
	{
		x = find_if(student.deq.begin(), student.deq.end(), IsCreditNum(Credit));
		student.ChangeStudentInfo(x);
	}
	void FindCourse(int Course)
	{
		copy_if(student.deq.begin(), student.deq.end(), student.helpDeq.begin(), IsCourse(Course));
		student.PrintSomeInfo();
	}
	void FindGroup(int Group)
	{
		copy_if(student.deq.begin(), student.deq.end(), student.helpDeq.begin(), IsGroup(Group));
		student.PrintSomeInfo();
	}
	void FindSurname(string Surname)
	{
		copy_if(student.deq.begin(), student.deq.end(), student.helpDeq.begin(), IsSurname(Surname));
		student.PrintSomeInfo();
	}
	void FindCredit(int Credit)
	{
		copy_if(student.deq.begin(), student.deq.end(), student.helpDeq.begin(), IsCreditNum(Credit));
		student.PrintSomeInfo();
	}
	void FindExcellent()
	{
		for (x = find_if(student.helpDeq.begin(),student.helpDeq.end(),IsExcellentMark());
			x != student.helpDeq.end(); x= find_if(++x,student.helpDeq.end(),IsExcellentMark()))
		{
			student.PrintInfo(x);
		}
	}
	void FindAvg(int min, int max)
	{
		for (x = find_if(student.helpDeq.begin(), student.helpDeq.end(), IsAvgMinMax(min,max));
			x != student.helpDeq.end(); x = find_if(++x, student.helpDeq.end(), IsAvgMinMax(min, max)))
		{
			student.PrintInfo(x);
		}
	}
};
