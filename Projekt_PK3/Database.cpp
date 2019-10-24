#include "Database.h"


Database::~Database()
{
	for (int i = 0; i < base.getSize(); i++)
		delete base[i];
}


inline void Database::addMedicine(Medicine *medicine)
{
	base.insert(getPosMedicine(medicine->name, true), medicine);
}


void Database::removeMedicine(const int pos)
{
	base[pos]->replacements.removeAll(base[pos]->name);
	base[pos]->prohibitedCombinations.removeAll(base[pos]->name);

	delete base[pos];
	base.erase(pos);
}


void Database::changeMedicine(const int pos, const std::string name)
{
	Medicine *med = base[pos];
	base[pos]->replacements.change(base[pos]->name, name);
	base[pos]->prohibitedCombinations.change(base[pos]->name, name);
	base[pos]->name = name;
	base.erase(pos);
	addMedicine(med);
}


bool Database::setLinkedList(const int pos, const std::string anotherName, setLinkedListMethod method)
{
	int anotherPos;
	if ((anotherPos = getPosMedicine(anotherName)) >= 0)
	{
		method(base, pos, anotherPos, base[pos]->name, anotherName);
		return true;
	}
	return false;
}


void Database::setReplacements(Vector<Medicine*> &base, const int pos, const int anotherPos, const std::string name, const std::string anotherName)
{
	if (!base[pos]->replacements.repeatControl(name, anotherName))
		base[pos]->replacements.add(name, anotherName, &base[anotherPos]->replacements);
}


void Database::setProhibitedCombinations(Vector<Medicine*> &base, const int pos, const int anotherPos, const std::string name, const std::string anotherName)
{
	if (!base[pos]->prohibitedCombinations.repeatControl(name, anotherName))
		base[pos]->prohibitedCombinations.add(name, anotherName, &base[anotherPos]->prohibitedCombinations);
}


bool  Database::removeLinkedList(const int pos, const std::string anotherName, removeLinkedListMethod method)
{
	return method(base, pos, base[pos]->name, anotherName);
}


bool Database::removeReplacements(Vector<Medicine*> &base, const int pos, const std::string name, const std::string anotherName)
{
	return base[pos]->replacements.remove(name, anotherName);
}


bool Database::removeProhibitedCombinations(Vector<Medicine*> &base, const int pos, const std::string name, const std::string anotherName)
{
	return base[pos]->prohibitedCombinations.remove(name, anotherName);
}


void Database::getBaseMedicine()
{
	for (int i = 0; i < base.getSize(); i++)
		std::cout << '-' << base[i]->name << std::endl;
}


void Database::getAllSearchMedicine(const StructMedicine structM)
{
	for (int i = 0; i < base.getSize(); i++)
	{
		if (base[i]->check(structM))
			std::cout << '-' << base[i]->name << std::endl;
	}
}


Medicine* Database::getMedicine(const std::string name)
{
	int pos;
	if ((pos = getPosMedicine(name)) >= 0)
		return base[pos];
	return nullptr;
}


int Database::getPosMedicine(const std::string name, const bool inequality)
{
	int left = 0;
	int right = base.getSize() - 1;
	int pos = 0;
	while (left <= right)
	{
		pos = (left + right) / 2;
		if (*base[pos] == name)
			return pos;
		if (*base[pos] > name)
			right = pos - 1;
		else
			left = pos + 1;
	}
	if (!inequality)	
		return -1;
	if(base.getSize())
		if(*base[pos] > name)
			return pos;
		else
			return pos + 1;
	return pos;
}


void Database::saveBase(std::string fileName)
{
	std::ofstream file(fileName, std::ios::binary);		//bez sprawdzania rozszerzenia pliku
	size_t size;
	
	for (int i = 0; i < base.getSize(); i++)
	{
		file.write(NEXT_MEDICINE, 2 * sizeof(char));

		saveString(file, base[i]->name);
		file.write((const char*)&base[i]->ageRestrictions, sizeof(int));
		saveString(file, base[i]->intended);
		saveString(file, base[i]->composition);
		base[i]->price *= 100;
		file.write((const char*)(int)(&base[i]->price), sizeof(float));
		file.write((const char*)&base[i]->reimbursedMedicine, sizeof(bool));
	}

	for (int i = 0; i < base.getSize(); i++)
	{
		file.write(RELATIONS, 2 * sizeof(char));
		for (int j = 0; j < base[i]->replacements.getSize(); j++)
		{
			file.write(NEXT_RELATIONS, 2 * sizeof(char));
			saveString(file, base[i]->replacements.get(j));
		}
		file.write(RELATIONS, 2 * sizeof(char));
		for (int j = 0; j < base[i]->prohibitedCombinations.getSize(); j++)
		{
			file.write(NEXT_RELATIONS, 2 * sizeof(char));
			saveString(file, base[i]->prohibitedCombinations.get(j));
		}
	}
	file.write(END_MEDICINE, sizeof(char));

	file.close();
}


bool Database::loadBase(std::string fileName)
{
	std::ifstream file(fileName, std::ios::binary);

	char step[2];
	StructMedicine structM;

	if (file.is_open())
	{
		file.read(step, 2 * sizeof(char));
		while (*step == *NEXT_MEDICINE)
		{
			structM.name = loadString(file);
			file.read((char*)&structM.ageRestrictions, sizeof(int));
			structM.intended = loadString(file);
			structM.composition = loadString(file);
			file.read((char*)(int)&structM.price, sizeof(float));
			structM.price /= 100;
			file.read((char*)&structM.reimbursedMedicine, sizeof(bool));

			base.push_back(new Medicine(structM));

			file.read(step, 2 * sizeof(char));
		}

		file.read(step, 2 * sizeof(char));
		for (int i = 0; i < base.getSize(); i++)
		{
			while (*step == *NEXT_RELATIONS)
			{
				structM.name = loadString(file);
				setLinkedList(i, structM.name, setReplacements);
				file.read(step, 2 * sizeof(char));
			}

			file.read(step, 2 * sizeof(char));
			while (*step == *NEXT_RELATIONS)
			{
				structM.name = loadString(file);
				setLinkedList(i, structM.name, setProhibitedCombinations);
				file.read(step, 2 * sizeof(char));
			}
		}
		file.close();
		return true;
	}
	file.close();
	return false;
}


inline void Database::saveString(std::ofstream & file, std::string &str)
{
	size_t size;
	size = str.size();
	file.write((char*)&size, sizeof(size_t));
	file.write(str.c_str(), size);
}


inline std::string Database::loadString(std::ifstream &file)
{
	size_t size;
	file.read((char*)&size, sizeof(size_t));

	char *buffer = new char[size + 1];
	file.read(buffer, size);

	buffer[size] = '\0';
	std::string str = buffer;
	delete[] buffer;

	return str;
}