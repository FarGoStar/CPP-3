

/* Задача №9
Справочник деканата
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include "IsGroup.h"
#include "IsCourse.h"
#include "IsCreditNum.h"
#include "IsFindStudentInfo.h"
#include "StudentInfoList.h"
#include "IsSurname.h"
#include "IsMark.h"
#include "IsDisc.h"
#include "IsFindForAvg.h"
#include "MyDeanery.h"

using namespace std;


void menu()
{
	cout << "1 — Зачислить студента" << endl;
	cout << "2 — Изменить данные о студенте" << endl;
	cout << "3 — Отчислить студента" << endl;
	cout << "4 — Вывести результаты сессии" << endl;
	cout << "Если хотите выйти из программы - нажмите 0" << endl;
	cout << "Ввод: ";
}

void submenu()
{
	cout << "1 — Вывести результаты по курсу" << endl;
	cout << "2 — Вывести результаты по номеру группы" << endl;
	cout << "3 — Вывести результаты по фамилии" << endl;
	cout << "4 — Вывести результаты по номеру зачетной книжки" << endl;
	cout << "Ввод: ";
}

void submenu2()
{
	cout << "1 — Вывести только отличников" << endl;
	cout << "2 — Вывести только студентов со средним баллом в заданном диапозоне" << endl;
	cout << "Ввод: ";
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	MyDeanery deanery = MyDeanery();
	deanery.Deserialize();
	bool control = true, control2 = true, control3 = true;
	StudentInfoList list;
	int _course;
	int _group;
	string _surname;
	int _creditNum;
	char tmp;
	int tmp2;
	char tmp3;
	int min, max;
	while (control) {
		menu();
		cin >> tmp;
		cin.get();
		cout << endl;

		switch (tmp) {
		case '1':
			deanery.AddStudent();
			deanery.Serialize();
			break;

		case '2':
			cout << "Введите номер зачетной книжки для изменения данных: ";  cin >> _creditNum; cout << endl;
			deanery.ChangeStudentInfo(_creditNum);
			deanery.Serialize();
			break;

		case '3':
			cout << "Введите номер зачетной книжки отчисляемого студента: ";  cin >> _creditNum; cout << endl;
			deanery.DeleteStudent(_creditNum);
			deanery.Serialize();
			cout << "Студент удален из справочника." << endl;
			break;
		case '4':
			while (control2)
			{
				submenu();
				cin >> tmp;
				cin.get();
				switch (tmp)
				{
				case '1':
					cout << "Курс: "; cin >> _course;
					deanery.FindCourse(_course);
					break;

				case '2':
					cout << "Номер группы: "; cin >> _group;
					deanery.FindGroup(_group);
					break;
				case '3':
					cout << "Фамилия: "; cin >> _surname;
					deanery.FindSurname(_surname);
					break;
				case '4':
					cout << "Номер зачетной книжки: "; cin >> _creditNum;
					deanery.FindCredit(_creditNum);
					break;
				case '0':
					control2 = false;
					break;
				}
				cout << "Отфильтровать результаты сессии по определенному критерию?" << endl;
				cout << "1 — Да" << endl;
				cout << "2 — Нет" << endl;
				cin >> tmp2;
				if (tmp2 == 1)
					while (control3)
					{
						submenu2();
						cin >> tmp3;
						switch (tmp3)
						{
						case '1': deanery.FindExcellent();
							break;
						case '2': cout << "Введите минимум для среднего балла по результатам сессии" << endl;
							cin >> min;
							cout << "Введите максимум для среднего балла по результатам сессии" << endl;
							cin >> max;
							deanery.FindAvg(min, max);
							break;
						case '0': control3 = false;
							break;
						}
					}
				break;
		case '0':
			control = false;
			break;

			}
		}

	}
}
