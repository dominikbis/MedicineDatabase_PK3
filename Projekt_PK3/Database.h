#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Medicine.h"

constexpr char NEXT_MEDICINE[] = "1";//czyta 'step' jako 2*char, przy zapisie i wczytywaniu
constexpr char RELATIONS[] = "2";
constexpr char NEXT_RELATIONS[] = "3";
constexpr char END_MEDICINE[] = "4";

typedef void(*setLinkedListMethod)(Vector<Medicine*> &, const int, const int, const std::string, const std::string);
typedef bool(*removeLinkedListMethod)(Vector<Medicine*> &, const int, const std::string, const std::string);


class Database
{
public:
	~Database();

	void addMedicine(Medicine *);
	void removeMedicine(const int);
	void changeMedicine(const int, const std::string);

	bool setLinkedList(const int, const std::string, setLinkedListMethod);
	static void setReplacements(Vector<Medicine*> &, const int, const int, const std::string, const std::string);
	static void setProhibitedCombinations(Vector<Medicine*> &, const int, const int, const std::string, const std::string);
	bool removeLinkedList(const int, const std::string, removeLinkedListMethod);
	static bool removeReplacements(Vector<Medicine*> &, const int, const std::string, const std::string);
	static bool removeProhibitedCombinations(Vector<Medicine*> &, const int, const std::string, const std::string);

	void getBaseMedicine();
	void getAllSearchMedicine(const StructMedicine);
	Medicine* getMedicine(const std::string);
	int getPosMedicine(const std::string, const bool = false);//-1 oznacza, ze nie znaleziono, bool tryb dzialania = <

	void saveBase(std::string);
	bool loadBase(std::string);

protected:
	Vector<Medicine*>base;

	void saveString(std::ofstream &, std::string &);
	std::string loadString(std::ifstream &);
};