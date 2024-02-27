/*
Name: Ario Nazemirad
Email: anazemirad@myseneca.ca
ID: 144647299
Date: Dec 3
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Perishable.h"
#include "Utils.h"

using namespace std;
namespace sdds {
	Perishable::Perishable() {
		m_handling = nullptr;
		new (&m_expiry) Date();
	}

	Perishable::~Perishable() {
		delete[] m_handling;
	}

	Perishable::Perishable(const Perishable& obj) : Item(obj) {
		if (obj) {
			m_expiry = obj.m_expiry;

			if (obj.m_handling != nullptr) {
				m_handling = new char[strlen(obj.m_handling) + 1];
				for (int i = 0; i < (int)strlen(obj.m_handling) + 1; i++)
					m_handling[i] = obj.m_handling[i];
			}
			else {
				m_handling = nullptr;
			}
		}
	}

	Perishable& Perishable::operator=(const Perishable& obj) {
		if (this != &obj) {
			m_expiry = obj.m_expiry;
			(Item&)*this = obj;

			delete[] m_handling;

			if (obj.m_handling != nullptr) {
				m_handling = new char[strlen(obj.m_handling) + 1];
				for (int i = 0; i < (int)strlen(obj.m_handling) + 1; i++)
					m_handling[i] = obj.m_handling[i];
			}
			else {
				m_handling = nullptr;
			}
		}
		return *this;
	}

	Date& Perishable::expiry() {
		return m_expiry;
	}

	int Perishable::readSku(std::istream& istr) {
		m_sku = ut.getint(10000, 39999, "SKU: ");
		return m_sku;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const {
		const_cast<Date&>(m_expiry).formatted(false);
		Item::save(ofstr);
		if (m_handling != nullptr) {
			ofstr << '\t' << m_handling << '\t';
			m_expiry.write(ofstr);
		}
		else {
			ofstr << '\t' << '\t';
			m_expiry.write(ofstr);
		}
		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr) {
		char newHandling[500];

		Item::load(ifstr);
		if (ifstr.peek() != '\t') {
			ifstr.get(newHandling, 500, '\t');
			delete[] m_handling;
			if (newHandling != nullptr) {
				m_handling = new char[strlen(newHandling) + 1];
				strcpy(m_handling, newHandling);
			}
		}
		else {
			delete[] m_handling;
			m_handling = nullptr;
		}
		if (ifstr.peek() != '\t') {
			m_state = "Input file stream read (perishable) failed!";
			ifstr.ignore(2000, '\n');
		}
		else {
			ifstr.ignore();
			m_expiry.read(ifstr);
		}

		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr) const {
		const_cast<Date&>(m_expiry).formatted(true);
		if (!this) {
			ostr << m_state;
		}
		else {
			if (m_linear == true) {
				Item::display(ostr);
				if (m_handling != nullptr && m_handling[0] != '\0') {
					ostr << "*";
				}
				else {
					ostr << " ";
				}
				m_expiry.write(ostr);
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: ";
				ostr << m_expiry << endl;
				if (m_handling != nullptr && m_handling[0] != '\0') {
					ostr << "Handling Instructions: " << m_handling << endl;
				}
			}
		}
		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr) {
		char newHandling[500];

		Item::read(istr);
		delete[] m_handling;
		m_handling = nullptr;

		istr.ignore();
		cout << "Expiry date (YYMMDD): ";
		istr >> m_expiry;
		cout << "Handling Instructions, ENTER to skip: ";
		istr.get(newHandling, 500, '\n');
		if (newHandling[0] != '\0') {
			if (newHandling != nullptr) {
				m_handling = new char[strlen(newHandling) + 1];
				strcpy(m_handling, newHandling);
			}
		}
		if (!istr) {
			m_state = "Perishable console date entry failed!";
		}
		istr.ignore(2000, '\n');
		return istr;
	}
};
