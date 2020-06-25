#pragma once
#include <deque>
#include "Elem.h"
#include <iterator>

//Используемый контейнер — deque
class StudentInfoList {
public:
	deque<Elem> deq;
	deque<Elem> helpDeq;

	StudentInfoList() : deq(), helpDeq() {}

	void Serialize(ofstream& ofs) {
		int size = deq.size();
		ofs.write((char*)&size, sizeof(int));
		for (Elem el : deq) {
			el.Serialize(ofs);
		}
	}

	void Deserialize(ifstream& ifs) {
		int size;
		ifs.read((char*)&size, sizeof(int));
		for (int i = 0; i < size; ++i) {
			Elem el;
			el.Deserialize(ifs);
			deq.push_front(el);
		}
	}

	void AddStudentInfo() 
	{
		istream_iterator<Elem> is;
		is = cin;
		deq.push_front(*is);
		cout << "Запись добавлена" << endl;
		cout << endl;		
	}

	void PrintInfo(deque<Elem>::iterator x) 
	{
		cout << *x;
	}

	void PrintSomeInfo() 
	{
		copy(helpDeq.begin(), helpDeq.end(), ostream_iterator<Elem>(cout, ""));
	}

	void DeleteStudentInfo(deque<Elem>::iterator x) 
	{
		deq.erase(x);
		cout << "Запись удалена из журнала" << endl;
		cout << endl;
	}

	void ChangeStudentInfo(deque<Elem>::iterator x) 
	{
		istream_iterator<Elem> is(cin);
		*x = *is;
		cout << "Запись в журнале сессии изменена" << endl;
		cout << endl;
	}

	void LoadToFile(ofstream& file, deque<Elem>::iterator x) 
	{
		ostream_iterator<Elem> is(file);
		*is = *x;
		cout << "Данные загружены в файл" << endl;
		cout << endl;
	}

	void LoadFromFile(ifstream& file) 
	{
		istream_iterator<Elem> is(file);
		deq.push_front(*is);
		cout << "Запись загружена из файла" << endl;
		cout << endl;
	}

	void LoadSomeInfoFromFile(ifstream& file) 
	{
		istream_iterator<Elem> is(file);
		while (!file.eof()) {
			deq.push_front(*is);
		}
		cout << "Все записи из файла загружены" << endl;
		cout << endl;
	}

};
