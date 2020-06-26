#pragma once
#include <deque>
#include "Elem.h"
#include <functional>

//Используемый контейнер — deque
template <typename T> class StudentInfoList
{
private:
	
	bool sorted = false;
	deque<T> deq;
	const string FILENAME = "Deanery.bin";

	void PrintInfo(deque<T>::iterator x) 
	{
		cout << *x;
	}

	void PrintSomeInfo() 
	{
		copy(deq.begin(), deq.end(), ostream_iterator<T>(cout, ""));
	}
public:
	typedef function<bool(const Elem&)> Predicate;
	void Serialize() {
		ofstream ofs(FILENAME, ios::binary | ios::out);
		int size = deq.size();
		ofs.write((char*)&size, sizeof(int));
		for (T el : deq) {
			el.Serialize(ofs);
		}
		ofs.close();
	}

	void Deserialize() {
		ifstream ifs(FILENAME, ios::binary | ios::in);
		int size;
		ifs.read((char*)&size, sizeof(int));
		for (int i = 0; i < size; ++i) {
			T el;
			el.Deserialize(ifs);
			deq.push_front(el);
		}
		ifs.close();
	}

	StudentInfoList() : deq() {}
	void AddStudentInfo()
	{
		istream_iterator<T> is;
		is = cin;
		deq.push_front(*is);
		cout << "Запись добавлена" << endl;
		cout << endl;
		sorted = false;
	}
	void remove_if(Predicate p)
	{
		auto end = deq.begin();
		for (auto i = deq.begin(); i < deq.end(); ++i)
		{
			if (!p(*i))
			{
				if (end != i)
					*end = *i;
				++end;
			}
		}
		deq.erase(end, deq.end());
	}
	void DeleteStudentInfo(Predicate pred)
	{
		remove_if(pred);
		cout << "Запись удалена из журнала" << endl;
		cout << endl;
	}
	int Find(Predicate pred) const
	{
		for (int i = 0; i < deq.size(); ++i  )
			if (pred(deq[i])) return i;
		return -1;
	}
	void ChangeStudentInfo(Predicate pred) 
	{
		int x = Find(pred);
		istream_iterator<Elem> is(cin);
		deq[x] = *is;
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
	
	void sort(function<bool(const T& a, const T& b)> lt)
	{
		std::sort(deq.begin(),deq.end(), lt);
		sorted = true;
	}
	int indexof_binary(function<int(const T& item)> dir)
	{
		if (!sorted)
		{
			cerr << "Контейнер не отсортирован\n";
			return -2;
		}

		int min = 0, max = deq.size() - 1;
		do {
			int i = (min + max) / 2;
			int d = dir(deq[i]);
			if (d == 0)
				return i;
			if (d < 0)
				max = i;
			else
				min = i + 1;
		} while (min < max);

		if (dir(deq[min]) == 0)
			return min;

		return -1;
	}
	StudentInfoList select(Predicate p)
	{
		StudentInfoList helpStud;
		for (auto i : deq)
			if (p(i))
				helpStud.deq.push_front(i);
		helpStud.PrintSomeInfo();
		return;
	}
	StudentInfoList operator=(StudentInfoList help)
	{
		copy(help.deq.begin(), help.deq.end(), deq.begin());
		return *this;
	}
};
