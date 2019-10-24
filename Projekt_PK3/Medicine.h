#pragma once

#include <iostream>
#include <string>

#include "StructMedicine.h"
#include "LinkedList.h"
#include "LinkedList.cpp"


class Medicine :
	public StructMedicine
{
public:
	using StructMedicine::StructMedicine;
	Medicine(StructMedicine &);
	Medicine(Medicine &);

	bool operator<(const Medicine &);
	bool operator<(const std::string &);
	bool operator>(const Medicine &);
	bool operator>(const std::string &);
	bool operator==(const std::string &);

	LinkedList<std::string> replacements;
	LinkedList<std::string> prohibitedCombinations;

	bool check(const StructMedicine &);		//do wyszukiwania
	void get();
};