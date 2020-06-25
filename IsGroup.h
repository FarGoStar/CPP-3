#pragma once
#include "Elem.h"

//Поиск подходящего номера группы
struct IsGroup {
	int group;

	IsGroup(int _group) {
		group = _group;
	}

	bool operator()(const Elem& e) {
		return e.group == group;
	}
};