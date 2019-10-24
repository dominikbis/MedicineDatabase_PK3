#include "Menu.h"


void Menu::medicineCreator()
{
	StructMedicine structM;

	do
	{
		system("cls");
		std::cout << "nazwy lekow nie moga sie powtarzac!\n\n\n";
		std::cout << "Podaj nazwe nowego leku: ";
		std::getline(std::cin, structM.name);
	} while (getPosMedicine(structM.name) >= 0);


	system("cls");
	do
	{
		std::cout << "Podaj od jakiego wieku mozna stosowac produkt(w latach): ";
	} while (!structM.readAgeRestrictions());

	system("cls");
	std::cout << "Podaj w jakim celu stosuje sie produkt: ";
	std::getline(std::cin, structM.intended);

	system("cls");
	std::cout << "Podaj sklad produktu: ";
	std::getline(std::cin, structM.composition);

	system("cls");
	do
	{
		std::cout << "Podaj cene produktu: ";
	} while (!structM.readPrice());

	system("cls");
	std::cout << "Podaj czy lek jest refundowany('t'-tak / dowolny inny klawisz - nie): ";
	if (_getch() == 't')
		structM.reimbursedMedicine = true;
	else
		structM.reimbursedMedicine = false;

	addMedicine(new Medicine(structM));

	system("cls");
	std::cout << "Lek zostal dodany do bazy!" << std::endl;
}


bool Menu::LinkedListCreatorAdd(const int pos, setLinkedListMethod method)
{
	std::string anotherName;
	std::cout << "Podaj nazwe produktu do dodania na liste: ";
	std::getline(std::cin, anotherName);
	if (!setLinkedList(pos, anotherName, method))
	{
		std::cout << "Produkt o podanej nazwie nie istnieje!" << std::endl;
		return false;
	}
	if (base[pos]->name == anotherName)
	{
		std::cout << "Produkt nie moze byc polaczony z samym soba!" << std::endl;
		return false;
	}
	std::cout << "Produkt zostal pomyslnie dodany na liste!" << std::endl;
	return true;
}


bool  Menu::LinkedListCreatorRemove(const int pos, removeLinkedListMethod method)
{
	std::string anotherName;
	std::cout << "Podaj nazwe produktu do usuniecia z listy: ";
	std::getline(std::cin, anotherName);
	if (!removeLinkedList(pos, anotherName, method))
	{
		std::cout << "Produkt o podanej nazwie nie istnieje!" << std::endl;
		return false;
	}
	std::cout << "Produkt zostal pomyslnie usuniety z listy!" << std::endl;
	return true;
}


void Menu::displayMenu()
{
	std::cout << std::endl << std::endl << "	Menu: " << std::endl << std::endl;
	std::cout << "[1] - Dodaj nowy lek do bazy danych" << std::endl;
	std::cout << "[2] - Usun lek z bazy danych" << std::endl;
	std::cout << "[3] - Wyswietl spis wszystkich lekow" << std::endl;
	std::cout << "[4] - Wyswietl informacje o danym leku" << std::endl;
	std::cout << "[5] - Wyszukaj lek" << std::endl;
	std::cout << std::endl;
	std::cout << "[6] - Zapisz baze danych" << std::endl;
	std::cout << "[7] - Wczytaj baze danych" << std::endl;
	std::cout << "[8] - Opcje automatycznego zapisu" << std::endl;
	std::cout << "[ESC] - Zamknij program" << std::endl;
}


void Menu::displayMenuMedicine()
{
	std::cout << std::endl << std::endl << "Opcje: " << std::endl;
	std::cout << "[1] - Edytuj informacje o wyswietlonym leku" << std::endl;
	std::cout << "[2] - Usun wyswietlony lek" << std::endl;
	std::cout << "[0] - Powrot do menu glownego" << std::endl;
}


void Menu::displayMenuMedicineEdit()
{
	std::cout << std::endl << std::endl << "Opcje edycji: " << std::endl;
	std::cout << "[1] - Zmien nazwe" << std::endl;
	std::cout << "[2] - Zmien ograniczenia wiekowe" << std::endl;
	std::cout << "[3] - Zmien informacje o dzialaniu leku" << std::endl;
	std::cout << "[4] - Zmien informacje o skladzie leku" << std::endl;
	std::cout << "[5] - Zmien cene leku" << std::endl;
	std::cout << "[6] - Zmien informacje na temat refundacji leku" << std::endl;
	std::cout << "[7] - Dodaj/usun zamienniki dla danego leku" << std::endl;
	std::cout << "[8] - Dodaj/usun leki na liscie niedozwolonych polaczen" << std::endl;
	std::cout << "[0] - Powrot" << std::endl;
}


void Menu::displayMenuMedicineEditLinkedList()
{
	std::cout << std::endl << std::endl << "Opcje: " << std::endl;
	std::cout << "[1] - Dodaj" << std::endl;
	std::cout << "[2] - Usun" << std::endl;
	std::cout << "[0] - Powrot" << std::endl;
}


void Menu::displayMenuSearch(const StructMedicine structM)
{
	std::cout << std::endl << std::endl << "Kryteria: " << std::endl;
	std::cout << "[1] - Nazwa: " << structM.name << std::endl;
	std::cout << "[2] - Ograniczenia wiekowe: ";
	if (structM.ageRestrictions)
		std::cout << structM.ageRestrictions << std::endl;
	else
		std::cout << "brak" << std::endl;
	std::cout << "[3] - Dzialanie: " << structM.intended << std::endl;
	std::cout << "[4] - Sklad: " << structM.composition << std::endl;
	std::cout << "[5] - Maksymalna cena: ";
	if (structM.price)
		std::cout << structM.price << std::endl;
	else
		std::cout << "brak" << std::endl;
	std::cout << "[6] - Czy refundowany: ";
	if (structM.reimbursedMedicine)
		std::cout << "tak" << std::endl;
	else
		std::cout << "nie" << std::endl;
	std::cout << "[7] - Wyswietl informacje o danym leku" << std::endl;
	std::cout << "[0] - Powrot" << std::endl;
}


void Menu::ActionMenu()
{
	choice = RESET_CHOICE;
	std::string name;
	int pos;

	while (choice != ASCII_ESC)
	{
		if (autoSave)
		{
			std::cout << "Autozapis wlaczony - Baza danych zostala zaktualizowana!\n\n";
			saveBase(autoSaveFileName);
		}
		displayMenu();
		choice = _getch();
		system("cls");

		switch (choice)
		{
		case '1':
			medicineCreator();
			break;
		case '2':
			std::cout << "Podaj nazwe leku do usuniecia: ";
			std::getline(std::cin, name);
			if ((pos = getPosMedicine(name)) >= 0)
			{
				removeMedicine(pos);
				std::cout << "Lek zostal pomyslnie usuniety" << std::endl;
			}
			else
				std::cout << "Nie znaleziono leku o podanej nazwie w bazie danych" << std::endl;
			break;
		case '3':
			std::cout << "	Wszystkie leki zapisane w bazie:" << std::endl;
			getBaseMedicine();
			break;
		case '4':
			std::cout << "Podaj nazwe leku: ";
			std::getline(std::cin, name);
			if ((pos = getPosMedicine(name)) >= 0)
				ActionMenuMedicine(pos);
			else
				std::cout << "Nie znaleziono leku o podanej nazwie w bazie danych" << std::endl;
			break;
		case '5':
			ActionMenuSearch();
			break;
		case '6':
			std::cout << "Podaj nazwe wraz z rozszeczeniem pliku do zapisu: ";
			std::getline(std::cin, name);
			saveBase(name);
			break;
		case '7':
			std::cout << "Podaj nazwe wraz z rozszeczeniem pliku do odczytu: ";
			std::getline(std::cin, name);
			if (loadBase(name))
				std::cout << "Baza danych zostala pomyslnie wczytana" << std::endl;
			else
				std::cout << "Nie znaleziono pliku o podanej nazwie" << std::endl;
			break;
		case '8':
			std::cout << "Czy baza danych ma byc automatycznie aktualizowana\n('t'-tak / dowolny inny klawisz - nie)?" << std::endl;
			if (_getch() == ASCII_t)
			{
				std::cout << "Podaj nazwe wraz z rozszeczeniem pliku do zapisu: ";
				std::getline(std::cin, autoSaveFileName);
				autoSave = true;
			}
			else
				autoSave = false;
			break;
		case ASCII_ESC:
			break;
		default:
			std::cout << "Niepoprawnie wybrana obcja" << std::endl;
			break;
		}
	}
}


void Menu::ActionMenuMedicine(int &pos)
{
	choice = RESET_CHOICE;

	while (choice != RETURN_MENU)
	{
		base[pos]->get();
		displayMenuMedicine();
		choice = _getch();
		system("cls");

		switch (choice)
		{
		case '1':
			ActionMenuMedicineEdit(pos);
			break;
		case '2':
			std::cout << "Czy na pewno chcesz usunac ten lek?" << std::endl;
			std::cout << "'t'- tak / dowolny inny klawisz - nie" << std::endl;
			if ((choice = _getch()) == ASCII_t)
			{
				removeMedicine(pos);
				choice = RETURN_MENU;
			}
			break;
		case RETURN_MENU:
			break;
		default:
			std::cout << "Niepoprawnie wybrana obcja" << std::endl;
			break;
		}
	}
}


void Menu::ActionMenuMedicineEdit(int &pos)
{
	choice = RESET_CHOICE;
	std::string name;

	while (choice != RETURN_MENU)
	{
		base[pos]->get();
		displayMenuMedicineEdit();
		choice = _getch();
		system("cls");

		switch (choice)
		{
		case '1':
			std::cout << "Podaj nowa nazwe leku: ";
			std::getline(std::cin, name);
			if (getPosMedicine(name) < 0)
			{
				changeMedicine(pos, name);
				std::cout << "Zmieniono pomyslnie nazwe leku: " << std::endl;
			}
			else
				std::cout << "Lek o podanej nazwie juz istnieje: " << std::endl;
			break;
		case '2':
			do
			{
				std::cout << "Podaj nowe ograniczenia wiekowe: ";
			} while (!base[pos]->readAgeRestrictions());
			break;
		case '3':
			std::cout << "Podaj nowe informacje dotyczace dzialania leku: ";
			std::getline(std::cin, name);
			base[pos]->intended = name;
			break;
		case '4':
			std::cout << "Podaj nowy sklad leku: ";
			std::getline(std::cin, name);
			base[pos]->composition = name;
			break;
		case '5':
			do
			{
				std::cout << "Podaj nowa cene leku: ";
			} while (!base[pos]->readPrice());
			break;
		case '6':
			std::cout << "Podaj czy lek jest refundowany('t'-tak / dowolny inny klawisz - nie): ";
			if (_getch() == ASCII_t)
				base[pos]->reimbursedMedicine = true;
			else
				base[pos]->reimbursedMedicine = false;
			break;
		case '7':
			ActionMenuMedicineEditLinkedList(pos, setReplacements, removeReplacements);
			break;
		case '8':
			ActionMenuMedicineEditLinkedList(pos, setProhibitedCombinations, removeProhibitedCombinations);
			break;
		case RETURN_MENU:
			break;
		default:
			std::cout << "Niepoprawnie wybrana obcja" << std::endl;
			break;
		}
	}
}


void Menu::ActionMenuMedicineEditLinkedList(const int &pos, setLinkedListMethod setMethod, removeLinkedListMethod removeMethod)
{
	choice = RESET_CHOICE;

	while (choice != RETURN_MENU)
	{
		displayMenuMedicineEditLinkedList();
		choice = _getch();
		system("cls");

		switch (choice)
		{
		case '1':
			if (LinkedListCreatorAdd(pos, setMethod))
				choice = RETURN_MENU;
			break;
		case '2':
			if (LinkedListCreatorRemove(pos, removeMethod))
				choice = RETURN_MENU;
			break;
		case RETURN_MENU:
			break;
		default:
			std::cout << "Niepoprawnie wybrana obcja" << std::endl;
			break;
		}
	}
	choice = RESET_CHOICE;
}


void Menu::ActionMenuSearch()
{
	choice = RESET_CHOICE;
	int pos;
	StructMedicine structM;

	while (choice != RETURN_MENU)
	{
		std::cout << "Wszystkie znalezione leki: " << std::endl;
		getAllSearchMedicine(structM);
		std::cout << std::endl;
		displayMenuSearch(structM);
		choice = _getch();
		system("cls");

		switch (choice)
		{
		case '1':
			std::cout << "Podaj kryteria nazwy: ";
			std::getline(std::cin, structM.name);
			break;
		case '2':
			do
			{
				std::cout << "Podaj kryteria ograniczen wiekowych: ";
			} while (!structM.readAgeRestrictions());
			break;
		case '3':
			std::cout << "Podaj kryteria dotyczace dzialania leku: ";
			std::getline(std::cin, structM.name);
			break;
		case '4':
			std::cout << "Podaj wymagany sklad leku: ";
			std::getline(std::cin, structM.name);
			break;
		case '5':
			do
			{
				std::cout << "Podaj maksymalna cene leku: ";
			} while (!structM.readPrice());
			break;
		case '6':
			std::cout << "Podaj czy lek ma byc obowiazkowo refundowany('t'-tak / dowolny inny klawisz - nie): ";
			if (_getch() == ASCII_t)
				structM.reimbursedMedicine = true;
			else
				structM.reimbursedMedicine = false;
			break;
		case '7':
			std::cout << "Podaj nazwe leku: ";
			std::getline(std::cin, structM.name);
			if ((pos = getPosMedicine(structM.name)) >= 0)
				ActionMenuMedicine(pos);
			else
				std::cout << "Nie znaleziono leku o podanej nazwie w bazie danych" << std::endl;
			break;
		case RETURN_MENU:
			break;
		default:
			std::cout << "Niepoprawnie wybrana obcja" << std::endl;
			break;
		}
	}
}