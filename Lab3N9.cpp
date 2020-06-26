

/* Задача №9
Справочник деканата
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include "StudentInfoList.h"


using namespace std;

typedef StudentInfoList<Elem>::Predicate Predicate;
typedef StudentInfoList<Elem> Students;
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
	Students stud,helpstud;
	stud.Deserialize();
	bool control = true, control2 = true, control3 = true;
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
			stud.AddStudentInfo();
			stud.Serialize();
			break;

		case '2':
			cout << "Введите номер зачетной книжки для изменения данных: ";  cin >> _creditNum; cout << endl;
			stud.Find([_creditNum](const Elem& e) {return e.creditNum == _creditNum; });
			stud.Serialize();
			break;

		case '3':
			cout << "Введите номер зачетной книжки отчисляемого студента: ";  cin >> _creditNum; cout << endl;
			stud.remove_if([_creditNum](const Elem& e) {return e.creditNum == _creditNum; });
			stud.Serialize();
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
					helpstud = stud.select([_course](const Elem& e) {return e.course == _course; });
					break;

				case '2':
					cout << "Номер группы: "; cin >> _group;
					helpstud = stud.select([_group](const Elem& e) {return e.group == _group; });
					break;
				case '3':
					cout << "Фамилия: "; cin >> _surname;
					helpstud = stud.select([_surname](const Elem& e) {return e.surname == _surname; });
					break;
				case '4':
					cout << "Номер зачетной книжки: "; cin >> _creditNum;
					helpstud = stud.select([_creditNum](const Elem& e) {return e.creditNum == _creditNum; });
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
						case '1': helpstud.select([](const Elem& e)
							{
								for (int i = 0; i < 5; i++)
								{
									if (e.marks[i] != 5) return false;
								};
								return true;
							});
							break;
						case '2': cout << "Введите минимум для среднего балла по результатам сессии" << endl;
							cin >> min;
							cout << "Введите максимум для среднего балла по результатам сессии" << endl;
							cin >> max;
							helpstud.select([min, max](const Elem& e) {double sum = 0; for (int i = 0; i < 5; i++)
																						{
																							sum += e.marks[i];
																						};
																						if (((sum / 5) < max) && ((sum / 5) > min)) return true;
																						else return false;});
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
