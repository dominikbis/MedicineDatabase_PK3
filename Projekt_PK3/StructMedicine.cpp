#include "StructMedicine.h"


StructMedicine::StructMedicine() :name(""), price(0), ageRestrictions(0), intended(""), composition(""), reimbursedMedicine(false)
{
}


StructMedicine::StructMedicine(const std::string name, const float price, const int ageRestrictions, const std::string intended, const std::string composition, const bool reimbursedMedicine) :
	name(name), price(price), ageRestrictions(ageRestrictions), intended(intended), composition(composition), reimbursedMedicine(reimbursedMedicine)
{
}


StructMedicine::StructMedicine(StructMedicine &structM) :
	name(structM.name), price(structM.price), ageRestrictions(structM.ageRestrictions), intended(structM.intended), composition(structM.composition), reimbursedMedicine(structM.reimbursedMedicine)
{
}


bool StructMedicine::readPrice()
{
	float  price2;
	std::cin >> price2;
	if (std::cin.fail())
	{
		system("cls");
		std::cin.clear();
		std::cin.ignore(100, '\n');
		return false;
	}
	std::cin.ignore(100, '\n');
	price = price2;
	return true;
}


bool StructMedicine::readAgeRestrictions()
{
	int ageRestrictions2;
	std::cin >> ageRestrictions2;
	if (std::cin.fail())
	{
		system("cls");
		std::cin.clear();
		std::cin.ignore(100, '\n');
		return false;
	}
	std::cin.ignore(100, '\n');
	ageRestrictions = ageRestrictions2;
	return true;
}