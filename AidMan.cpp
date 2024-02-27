//Ario Nazemirad
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "AidMan.h"
#include "Perishable.h"
#include "Item.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	int AidMan::menu() const {
		cout << "Aid Management System" << endl;
		cout << "Date: " << Date() << endl;
		cout << "Data file: ";
		if (fileName == nullptr) {
			cout << "No file" << endl;
		}
		else {
			cout << fileName << endl;
		}
		cout << "---------------------------------" << endl;

		return mainMenu.run();
	}

	AidMan::AidMan(const char* file) {
		const char* m_default = "List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database";
		new (&mainMenu) Menu(m_default);
		if (file != nullptr) {
			fileName = new char[strlen(file) + 1];
			strcpy(fileName, file);
		}
		else {
			fileName = nullptr;
		}
	}

	AidMan::~AidMan() {
		delete[] fileName;
		for (int i = 0; i < numOfItems; i++) {
			delete iProductPointers[i];
		}
	}

	void AidMan::allocateAndCopy(const char* name) {
		delete[] fileName;

		if (name != nullptr) {
			fileName = new char[strlen(name) + 1];
			for (int i = 0; i < (int)strlen(name) + 1; i++)
				fileName[i] = name[i];
		}
		else {
			fileName = nullptr;
		}
	}

	void AidMan::saveData() {
		if (fileName != nullptr) {
			std::ofstream ofstr;
			ofstr.open(fileName);
			for (int i = 0; i < numOfItems; i++) {
				iProductPointers[i]->save(ofstr);
				ofstr << endl;
			}
		}
	}

	void AidMan::dallocateData() {
		for (int i = 0; i < numOfItems; i++) {
			delete iProductPointers[i];
		}
		numOfItems = 0;
	}

	bool AidMan::loadData() {
		int select;
		char firstDigit;
		char name[50];
		int i = 0;

		saveData();
		numOfItems = 0;
		dallocateData();
		cout << "Enter file name: ";
		cin >> name;
		allocateAndCopy(name);
		ifstream file;
		file.open(fileName);
		if (!file.is_open()) {
			cout << "Failed to open " << fileName << " for reading!" << endl;
			cout << "Would you like to create a new data file?" << endl;
			cout << "1- Yes!" << endl;
			cout << "0- Exit" << endl;
			cout << "> ";
			select = ut.getint(0, 1);
			if (select == 1) {
				ofstream out(fileName);
			}
			else {
				delete[] fileName;
				fileName = nullptr;
			}
		}
		else {
			while (!file.eof()) {
				firstDigit = file.peek();
				if (firstDigit == '1' || firstDigit == '2' || firstDigit == '3') {
					iProductPointers[numOfItems] = new Perishable;
				}
				else if (firstDigit == '4' || firstDigit == '5' || firstDigit == '6' || firstDigit == '7' || firstDigit == '8' || firstDigit == '9') {
					iProductPointers[numOfItems] = new Item;
				}
				else {
					file.setstate(ios::failbit);
				}
				if (file.good()) {
					iProductPointers[numOfItems]->load(file);
					if (file.good()) {
						numOfItems++;
					}
					else {
						delete iProductPointers[i];
					}
				}
			}
		}
		return numOfItems > 0 ? true : false;
	}

	int AidMan::list(const char* sub_desc) {
		int i = 0, num = 0;
		char select;
		if (sub_desc == nullptr) {
			if (numOfItems != 0) {
				cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
				cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
				for (i = 0; i < numOfItems; i++) {
					cout.width(4);
					cout << i + 1 << " | ";
					iProductPointers[i]->linear(true);
					iProductPointers[i]->display(cout);
					cout << endl;
				}
				cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
				cout << "Enter row number to display details or <ENTER> to continue:" << endl;
				cout << "> ";
				cin.ignore(2000, '\n');
				select = cin.get();
				if (select != '\n') {
					num = (int)select - 48;
					iProductPointers[num - 1]->linear(false);
					iProductPointers[num - 1]->display(cout);
					cout << endl;
				}
				cout << endl;
			}
			else {
				cout << "The list is emtpy!" << endl;
			}
		}
		else {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (i = 0; i < numOfItems; i++) {
				if (*iProductPointers[i] == sub_desc) {
					cout.width(4);
					cout << i + 1 << " | ";
					iProductPointers[i]->linear(true);
					iProductPointers[i]->display(cout);
					cout << endl;
					num++;
				}
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		}
		return num;
	}

	int AidMan::search(int sku) const {
		int i = 0;
		int index = -1;
		for (i = 0; i < numOfItems - 1; i++) {
			if (*iProductPointers[i] == sku) {
				index = i;
			}
		}
		return index;
	}

	void AidMan::addItem() {
		int select, findSku;

		if (numOfItems >= sdds_max_num_items) {
			cout << "Database full!" << endl;
		}
		else {
			cout << "1- Perishable" << endl;
			cout << "2- Non-Perishable" << endl;
			cout << "-----------------" << endl;
			cout << "0- Exit" << endl;
			cout << "> ";
			cin >> select;
			if (select == 0) {
				cout << "Aborted" << endl;
			}
			else if (select == 1) {
				iProductPointers[numOfItems] = new Perishable;
				findSku = iProductPointers[numOfItems]->readSku(cin);
				if (search(findSku) == -1) {
					iProductPointers[numOfItems]->read(cin);
					numOfItems++;
					saveData();
				}
				else {
					cout << "Sku: " << findSku << " is already in the system, try updating quantity instead." << endl;
					delete iProductPointers[numOfItems];
				}
			}
			else if (select == 2) {
				iProductPointers[numOfItems] = new Item;
				findSku = iProductPointers[numOfItems]->readSku(cin);
				if (search(findSku) == -1) {
					iProductPointers[numOfItems]->read(cin);
					numOfItems++;
					saveData();
				}
				else {
					cout << "Sku: " << findSku << " is already in the system, try updating quantity instead." << endl;
					delete iProductPointers[numOfItems];
				}
			}
			cout << endl;
		}
	}

	void AidMan::remove(int index) {
		int i, j = index + 1;
		delete iProductPointers[index];
		for (i = index; i < numOfItems - 1; i++) {
			iProductPointers[i] = iProductPointers[j];
			j++;
		}
		numOfItems--;
	}

	void AidMan::removeItem() {
		char item[200];
		int sku, index, select;

		cout << "Item description: ";
		cin >> item;
		if (list(item) != 0) {
			cout << "Enter SKU: ";
			cin >> sku;
			index = search(sku);
			if (index == -1) {
				cout << "SKU not found!";
			}
			else {
				cout << "Following item will be removed: " << endl;
				iProductPointers[index]->linear(false);
				iProductPointers[index]->display(cout);
				cout << endl;
				cout << "Are you sure?" << endl;
				cout << "1- Yes!" << endl;
				cout << "0- Exit" << endl;
				cout << "> ";
				select = ut.getint(0, 1);
				if (select == 1) {
					remove(index);
					saveData();
					cout << "Item removed!" << endl;
				}
				else {
					cout << "Aborted!" << endl;
				}
				cout << endl;
			}

		}
	}

	void AidMan::updateQuantity() {
		char item[200];
		int sku, index, select, num;
		cout << "Item description: ";
		cin >> item;
		if (list(item) != 0) {
			cout << "Enter SKU: ";
			cin >> sku;
			index = search(sku);
			if (index == -1) {
				cout << "SKU not found!";
			}
			else {
				cout << "1- Add" << endl;
				cout << "2- Reduce" << endl;
				cout << "0- Exit" << endl;
				cout << "> ";
				select = ut.getint(0, 2);
				if (select == 1) {
					if (iProductPointers[index]->qtyNeeded() != iProductPointers[index]->qty()) {
						num = ut.getint(1, iProductPointers[index]->qtyNeeded() - iProductPointers[index]->qty(), "Quantity to add: ");
						*iProductPointers[index] += num;
						saveData();
						cout << num << " items added!" << endl;
					}
					else {
						cout << "Quantity Needed already fulfilled!" << endl;
					}
				}
				else if (select == 2) {
					if (iProductPointers[index]->qty() != 0) {
						num = ut.getint(1, iProductPointers[index]->qty(), "Quantity to reduce: ");
						*iProductPointers[index] -= num;
						saveData();
						cout << num << " items removed!" << endl;
					}
					else {
						cout << "Quaintity on hand is zero!" << endl;
					}
				}
				else {
					cout << "Aborted!" << endl;
				}
				cout << endl;
			}
		}
	}

	void AidMan::sort() {
		iProduct* temp[1];
		int i, j;

		for (i = 0; i < numOfItems; i++) {
			for (j = i + 1; j < numOfItems; j++) {
				if (iProductPointers[i]->qtyNeeded() - iProductPointers[i]->qty() < iProductPointers[j]->qtyNeeded() - iProductPointers[j]->qty()) {
					temp[0] = iProductPointers[i];
					iProductPointers[i] = iProductPointers[j];
					iProductPointers[j] = temp[0];
				}
			}
		}
		cout << "Sort completed!\n" << endl;
		saveData();
	}

	void AidMan::shipItems() {
		int i, num = 0;

		ofstream file;
		file.open("shippingOrder.txt");
		if (file.is_open()) {
			file << "Shipping Order, Date: " << Date() << endl;
			file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (i = 0; i < numOfItems; i++) {
				if (iProductPointers[i]->qtyNeeded() == iProductPointers[i]->qty()) {
					file.width(4);
					file << num + 1 << " | ";
					iProductPointers[i]->linear(true);
					iProductPointers[i]->display(file);
					file << endl;
					num++;
					remove(i);
				}
			}
			file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			cout << "Shipping Order for " << num << " times saved!" << endl;
			cout << endl;
			saveData();
			file.close();
		}
	}

	void AidMan::run() {
		int selection = -1;

		while (selection != 0) {
			selection = menu();
			if (selection != 0 && selection != 7 && fileName == nullptr) {
				selection = 7;
			}
			switch (selection) {
			case 0:
				cout << "Exiting Program!" << endl;
				break;
			case 1:
				cout << endl << "****List Items****" << endl;
				list();
				break;
			case 2:
				cout << endl << "****Add Item****" << endl;
				addItem();
				break;
			case 3:
				cout << endl << "****Remove Item****" << endl;
				removeItem();
				break;
			case 4:
				cout << endl << "****Update Quantity****" << endl;
				updateQuantity();
				break;
			case 5:
				cout << endl << "****Sort****" << endl;
				sort();
				break;
			case 6:
				cout << endl << "****Ship Items****" << endl;
				shipItems();
				break;
			case 7:
				cout << endl << "****New/Open Aid Database****" << endl;
				if (loadData() == true) {
					cout << numOfItems << " records loaded!" << endl << endl;
				}
				break;
			}

		}
	}
}
