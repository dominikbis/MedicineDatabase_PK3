#include "Medicine.h"


Medicine::Medicine(StructMedicine &structM)
{
	this->name = structM.name;
	this->ageRestrictions = structM.ageRestrictions;
	this->intended = structM.intended;
	this->composition = structM.composition;
	this->price = structM.price;
	this->reimbursedMedicine = structM.reimbursedMedicine;
}


Medicine::Medicine(Medicine &med)
{
	this->name = med.name;
	this->ageRestrictions = med.ageRestrictions;
	this->intended = med.intended;
	this->composition = med.composition;
	this->price = med.price;
	this->reimbursedMedicine = med.reimbursedMedicine;
	this->replacements = med.replacements;
	this->prohibitedCombinations = med.prohibitedCombinations;
}




bool Medicine::operator<(const Medicine &medicine)
{
	if (this->name < medicine.name)
		return true;
	return false;
}


bool Medicine::operator<(const std::string &name)
{
	if (this->name < name)
		return true;
	return false;
}


bool Medicine::operator>(const Medicine &medicine)
{
	if (this->name > medicine.name)
		return true;
	return false;
}


bool Medicine::operator>(const std::string &name)
{
	if (this->name > name)
		return true;
	return false;
}


bool Medicine::operator==(const std::string &name)
{
	if (this->name == name)
		return true;
	return false;
}




bool Medicine::check(const StructMedicine &structM)
{
	if (this->name.find(structM.name) != std::string::npos &&
		(!structM.price || this->price <= structM.price) &&
		(!structM.ageRestrictions || this->ageRestrictions <= structM.ageRestrictions) &&
		this->intended.find(structM.intended) != std::string::npos &&
		this->composition.find(structM.composition) != std::string::npos &&
		(!structM.reimbursedMedicine || this->reimbursedMedicine == structM.reimbursedMedicine))
		return true;
	return false;
}


void Medicine::get()
{
	std::cout << std::endl << "Nazwa: " << name << std::endl << std::endl;

	std::cout << "Ograniczenia wiekowe: " << ageRestrictions << " lat" << std::endl;
	std::cout << "Dzialanie: " << intended << std::endl;
	std::cout << "Sklad: " << composition << std::endl << std::endl;

	std::cout << "Cena: " << price << std::endl << std::endl;
	std::cout << "Refundowany: ";
	if (reimbursedMedicine)
		std::cout << "tak" << std::endl;
	else
		std::cout << "nie" << std::endl;

	std::cout << "Zamienniki: " << std::endl;
	replacements.getAll();
	std::cout << "Nie nalezy laczyc z: " << std::endl;
	prohibitedCombinations.getAll();
}