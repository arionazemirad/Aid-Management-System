//Ario Nazemirad
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Date.h"
#include "Status.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	bool Date::validate() {
		bool result = false;
		if (year < 2023 || year > maxYear) {
			m_state = "Invalid year in date";
			m_state = 1;
		}
		else if (month < 1 || month > 12) {
			m_state = "Invalid month in date";
			m_state = 2;
		}
		else if (day < 1 || day > ut.daysOfMon(month, year)) {
			m_state = "Invalid day in date";
			m_state = 3;
		}
		else {
			m_state.clear();
			result = true;
		}
		return result;
	}

	int Date::unique() const {
		return year * 372 + month * 31 + day;
	}

	Date::Date() {
		ut.getSystemDate(&year, &month, &day);
		validate();
		format = true;
	}

	Date::Date(int newYear, int newMonth, int newDay) {
		year = newYear;
		month = newMonth;
		day = newDay;
		validate();
		format = true;
	}

	Date::~Date() {
		m_state.clear();
	}

	bool Date::operator==(const Date& obj) const {
		return unique() == obj.unique();
	}

	bool Date::operator!=(const Date& obj) const {
		return unique() != obj.unique();
	}

	bool Date::operator<(const Date& obj) const {
		return unique() < obj.unique();
	}

	bool Date::operator>(const Date& obj) const {
		return unique() > obj.unique();
	}

	bool Date::operator<=(const Date& obj) const {
		return unique() <= obj.unique();
	}

	bool Date::operator>=(const Date& obj) const {
		return unique() >= obj.unique();
	}

	Status& Date::state() {
		return m_state;
	}

	Date& Date::formatted(bool newFormat) {
		format = newFormat;
		return *this;
	}

	Date::operator bool() const {
		return (const char*)(m_state);
	}

	std::ostream& Date::write(std::ostream& os) const {
		if (format == true) {
			os << year;
			os << "/";
			os.width(2);
			os.fill('0');
			os << month;
			os << "/";
			os.width(2);
			os.fill('0');
			os << day;
		}
		else {
			os << year - 2000;
			os.width(2);
			os.fill('0');
			os << month;
			os.width(2);
			os.fill('0');
			os << day;
		}
		os.fill(' ');

		return os;
	}

	int Date::stringToInt(char* str) {
		int result = 0, i;

		for (i = 0; str[i] != '\0'; ++i) {
			result = result * 10 + str[i] - '0';
		}
		return result;
	}

	bool Date::validDigit(char* str) {
		bool result = true;
		for (int i = 0; i < (int)(strlen(str)); i++) {
			if (!(str[i] >= 48 && str[i] <= 57)) {
				result = false;
			}
		}
		return result;
	}

	std::istream& Date::read(std::istream& is) {
		char yearString[5] = { '2', '0' };
		char string1[3] = {}, string2[3] = {}, string3[3] = {};

		is.get(string1, 3);
		if (is.peek() != '\n') {
			is.get(string2, 3);
		}
		if (is.peek() != '\n') {
			is.get(string3, 3);
		}
		if (validDigit(string1) && validDigit(string2) && validDigit(string3)) {
			if (strlen(string1) + strlen(string2) + strlen(string3) == 6) {
				strcat(yearString, string1);
				year = stringToInt(yearString);
				month = stringToInt(string2);
				day = stringToInt(string3);
			}
			else if (strlen(string1) + strlen(string2) + strlen(string3) == 4) {
				month = stringToInt(string1);
				day = stringToInt(string2);
			}
			else if (strlen(string1) + strlen(string2) + strlen(string3) == 2) {
				day = stringToInt(string1);
				month = stringToInt(string2);
			}
		}
		else {
			m_state = "Invalid date value";
			m_state = 0;
			is.setstate(ios::badbit);
		}
		if (is) {
			if (!validate()) {
				is.setstate(ios::badbit);
			}
		}
		is.ignore(2000, '\n');
		return is;
	}

	Date& Date::operator=(const Date& obj) {
		if (this != &obj) {
			year = obj.year;
			month = obj.month;
			day = obj.day;
			format = obj.format;
			m_state.clear();
			m_state = obj.m_state;
		}
		return *this;
	}

	Date::Date(const Date& obj) {
		if (obj) {
			year = obj.year;
			month = obj.month;
			day = obj.day;
			format = obj.format;
			m_state.clear();
			m_state = obj.m_state;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Date& obj) {
		obj.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, Date& obj) {
		obj.read(is);
		return is;
	}
};
