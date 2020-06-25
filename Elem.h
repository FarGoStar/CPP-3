#pragma once
#include <iostream>
#include <fstream>
using namespace std;
struct session {
	string disc;
	int mark;
};
//Класс записи
class Elem {
public:
	int course;
	int group;
	string surname;
	int creditNum;
	string disc[5] = { "ЯСП", "Язык C#", "Математический анализ", "Веб-верстка", "Структуры и алгоритмы" };
	int marks[5];

	Elem(int _course, int _group, string _surname,
		int _creditNum, int _marks[])
	{
		course	  = _course;
		group	  = _group;
		surname	  = _surname;
		creditNum = _creditNum;
		for (int i = 0; i < 5; i++)
		{
			marks[i] = _marks[i];
		}

	}

	Elem() 
	{
		course	  = 1;
		group	  = 1;
		surname	  = "Иванов";
		creditNum = 100;
		for (int i = 0; i < 5; i++)
			marks[i] = 0;
	}

	Elem& operator=(const Elem& e) {
		course	  = e.course;
		group	  = e.group;
		surname	  = e.surname;
		creditNum = e.creditNum;
		for (int i = 0; i < 5; i++)
			marks[i] = e.marks[i];
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Elem& e)
	{
		if (typeid(os) == typeid(ofstream))
		{
			os << e.course << endl;
			os << e.group << endl;
			os << e.surname << endl;
			os << e.creditNum << endl;
			for (int i = 0; i < 5; i++)
			{
				os << e.disc[i] << " " << e.marks[i] << endl;
			}
			return os;
		}
		else
		{

			os << "Запись в журнале сессии: " << endl;
			os << "Курс: " << e.course << " Группа: " << e.group << endl;
			os << "Фамилия: " << e.surname << endl;
			os << "Номер зачетной книжки: " << e.creditNum << endl;
			os << "Результаты сессии: " << endl;
			for (int i = 0; i < 5; i++)
			{
				os << e.disc[i] << " " << e.marks[i] << endl;
			}
			return os;
		}
	}

	friend istream& operator>>(istream& is, Elem& e) {

		cout << "Введите запись в справочник деканата: " << endl;
		cout << endl;

		int course;
		int group;
		string surname;
		int creditNum;
		int marks[5];
		cout << "Курс: "; is >> course;
		cout << "Группа: "; is >> group;
		cout << "Фамилия: "; is >> surname;
		cout << "Номер зачетной книжки: "; is >> creditNum;
		for (int i = 0; i < 5; i++)
		{
			cout << "Оценки: "; is >> marks[i];			
		}
		e = Elem(course, group, surname, creditNum, marks);
		return is;
	}
	void Serialize(ofstream& ofs) {
		ofs.write((char*)&course, sizeof(int));
		ofs.write((char*)&group, sizeof(int));
		int stringSize = surname.size();
		ofs.write((char*)&stringSize, sizeof(int));
		for (int i = 0; i < stringSize; ++i) {
			char c = surname[i];
			ofs.write(&c, sizeof(char));
		}
		ofs.write((char*)&creditNum, sizeof(int));
		for (int i = 0; i < 5; i++)
		{
			stringSize = disc[i].size();
			ofs.write((char*)&stringSize, sizeof(int));
			for (int j = 0; j < stringSize; ++j) {
				char c = disc[i][j];
				ofs.write(&c, sizeof(char));
			}
			ofs.write((char*)&marks[i], sizeof(int));
		}
	}

	void Deserialize(ifstream& ifs) {
		ifs.read((char*)&course, sizeof(int));
		ifs.read((char*)&group, sizeof(int));
		int stringSize;
		ifs.read((char*)&stringSize, sizeof(int));
		string _surname;
		for (int i = 0; i < stringSize; ++i) {
			char c;
			ifs.read(&c, sizeof(char));
			_surname += c;
		}
		surname = _surname;
		ifs.read((char*)&creditNum, sizeof(int));
		ifs.read((char*)&stringSize, sizeof(int));
		string _disc;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < stringSize; ++j) {
				char c;
				ifs.read(&c, sizeof(char));
				_disc[i] += c;
			}
			disc[i] = _disc[i];
			ifs.read((char*)&marks[i], sizeof(int));
		}
	}
};
