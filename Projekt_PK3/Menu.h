#pragma once

#include <iostream>
#include <string>
#include <conio.h>

#include "Database.h"

constexpr int ASCII_ESC = 27;
constexpr char RETURN_MENU = '0';
constexpr char RESET_CHOICE = 0;
constexpr char ASCII_t = 't';


class Menu :
	private Database
{
public:
	void ActionMenu();		//start

private:
	void ActionMenuMedicine(int &);
	void ActionMenuMedicineEdit(int &);
	void ActionMenuMedicineEditLinkedList(const int &, setLinkedListMethod, removeLinkedListMethod);
	void ActionMenuSearch();

	void displayMenu();
	void displayMenuMedicine();
	void displayMenuMedicineEdit();
	void displayMenuMedicineEditLinkedList();
	void displayMenuSearch(const StructMedicine);

	void medicineCreator();
	bool LinkedListCreatorAdd(const int, setLinkedListMethod);
	bool LinkedListCreatorRemove(const int, removeLinkedListMethod);


	char choice;
	bool autoSave = false;
	std::string autoSaveFileName;
};

