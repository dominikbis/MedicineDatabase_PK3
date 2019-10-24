#pragma once

#include <iostream>


class StructMedicine
{
public:
	StructMedicine();
	StructMedicine(const std::string, const float, const int, const std::string, const std::string, const bool);
	StructMedicine(StructMedicine &);

	std::string name;
	float  price;
	int ageRestrictions;
	std::string intended;
	std::string composition;
	bool reimbursedMedicine;

	bool readPrice();
	bool readAgeRestrictions();
};

