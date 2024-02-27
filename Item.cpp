//Ario Nazemirad
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Item.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	bool Item::isLinear() {
		return m_linear;
	}

	Item::Item() {
		m_price = 0;
		m_qty = 0;
		m_qtyNeeded = 0;
		m_description = nullptr;
		m_linear = false;
		m_sku = 0;
		m_state.clear();
	}

	Item::~Item() {
		delete[] m_description;
	}

	Item::operator double()const {
		return m_price;
	}

	Item::operator bool()const {
		return bool(m_state);
	}

	int Item::qtyNeeded()const {
		return m_qtyNeeded;
	}

	int Item::qty()const {
		return m_qty;
	}

	int Item::operator-=(int qty) {
		return m_qty -= qty;
	}

	int Item::operator+=(int qty) {
		return m_qty += qty;
	}

	void Item::linear(bool isLinear) {
		m_linear = isLinear;
	}

	void Item::clear() {
		m_state.clear();
	}

	bool Item::operator==(int sku)const {
		return m_sku == sku;
	}

	bool Item::operator==(const char* description)const {
		bool result = false;
		if (description != nullptr || m_description != nullptr) {
			if (strstr(m_description, description) != nullptr) {
				result = true;
			}
		}
		return result;
	}

	std::ofstream& Item::save(std::ofstream& ofstr)const {
		if (this) {
			ofstr.precision(2);
			ofstr.setf(ios::fixed);
			ofstr << m_sku << '\t' << m_description << '\t' << m_qty << '\t' << m_qtyNeeded << '\t' << m_price;
		}
		return ofstr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr) {
		char newDescription[500];

		if (!ifstr) {
			m_state = "Input file stream read failed!";
		}
		else {
			ifstr >> m_sku;
			ifstr.ignore();
			ifstr.get(newDescription, 500, '\t');
			delete[] m_description;
			if (newDescription != nullptr) {
				m_description = new char[strlen(newDescription) + 1];
				strcpy(m_description, newDescription);
			}
			ifstr.ignore();
			ifstr >> m_qty;
			ifstr.ignore();
			ifstr >> m_qtyNeeded;
			ifstr.ignore();
			ifstr >> m_price;
			ifstr.ignore();
		}

		return ifstr;
	}

	std::ostream& Item::display(std::ostream& ostr)const {
		int i;
		double neededAmount = 0.00;

		if (m_description != nullptr) {
			if (m_linear == true) {
				ostr.width(4);
				ostr << m_sku << " | ";
				if (strlen(m_description) > 35) {
					for (i = 0; i < 35; i++) {
						ostr << m_description[i];
					}
					ostr << " | ";
				}
				else {
					ostr.setf(ios::left);
					ostr.width(35);
					ostr << m_description << " | ";
				}
				ostr.unsetf(ios::left);
				ostr.width(4);
				ostr << m_qty << " | ";
				ostr.width(4);
				ostr << m_qtyNeeded << " | ";
				ostr.width(7);
				ostr.precision(2);
				ostr.setf(ios::fixed);
				ostr << m_price << " |";
			}
			else {
				ostr << "AMA Item:" << endl;
				ostr << m_sku << ": " << m_description << endl;
				ostr << "Quantity Needed: " << m_qtyNeeded << endl;
				ostr << "Quantity Available: " << m_qty << endl;
				ostr.precision(2);
				ostr.setf(ios::fixed);
				ostr << "Unit Price: $" << m_price << endl;
				if (m_qtyNeeded > m_qty) {
					neededAmount = (m_qtyNeeded - m_qty) * m_price;
				}
				ostr.precision(2);
				ostr.setf(ios::fixed);
				ostr << "Needed Purchase Fund: $" << neededAmount << endl;
			}
		}
		else {
			ostr << m_state;
		}
		return ostr;
	}

	std::istream& Item::read(std::istream& istr) {
		char newDescription1[500];
		char newDescription2[500];
		double num;
		bool valid = false;

		delete[] m_description;
		clear();

		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_sku << endl;

		cout << "Description: ";
		istr >> newDescription1;
		istr.getline(newDescription2, 500);
		strcat(newDescription1, newDescription2);
		if (newDescription1 != nullptr) {
			m_description = new char[strlen(newDescription1) + 1];
			strcpy(m_description, newDescription1);
		}

		m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
		m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ");
		cout << "Unit Price: $";

		do {
			while (!valid) {
				istr >> num;
				if (istr.fail())
				{
					cout << "Invalid number, retry: ";
					istr.clear();
					istr.ignore(2000, '\n');
				}
				else
				{
					valid = true;
				}
			}
			if (num < 0.0 || num > 9999.0) {
				cout << "Value out of range [" << "0.00" << "<=val<=" << "9999.00" << "]: ";
				valid = false;
			}
		} while (num < 0.0 || num > 9999.0);
		m_price = num;
		if (!istr) {
			m_state = "Console entry failed!";
		}
		return istr;
	}

	int Item::readSku(std::istream& istr) {
		m_sku = ut.getint(40000, 99999, "SKU: ");
		return m_sku;
	}

	Item& Item::operator=(const Item& obj) {
		if (this != &obj) {
			m_price = obj.m_price;
			m_qty = obj.m_qty;
			m_qtyNeeded = obj.m_qtyNeeded;
			m_linear = obj.m_linear;
			m_state = obj.m_state;
			m_sku = obj.m_sku;

			delete[]  m_description;
			if (obj.m_description != nullptr) {
				m_description = new char[strlen(obj.m_description) + 1];
				for (int i = 0; i < (int)strlen(obj.m_description) + 1; i++)
					m_description[i] = obj.m_description[i];
			}
			else {
				m_description = nullptr;
			}
		}
		return *this;
	}

	Item::Item(const Item& obj) {
		if (obj) {
			m_price = obj.m_price;
			m_qty = obj.m_qty;
			m_qtyNeeded = obj.m_qtyNeeded;
			m_linear = obj.m_linear;
			m_state = obj.m_state;
			m_sku = obj.m_sku;

			if (obj.m_description != nullptr) {
				m_description = new char[strlen(obj.m_description) + 1];
				for (int i = 0; i < (int)strlen(obj.m_description) + 1; i++)
					m_description[i] = obj.m_description[i];
			}
			else {
				m_state = "Input file stream read failed!";
				m_description = nullptr;
			}
		}
	}
}
