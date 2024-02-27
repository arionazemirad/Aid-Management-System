//Ario Nazemirad
#ifndef DATE_H
#define DATE_H
#include "Status.h"
namespace sdds {
	const int maxYear = 2030;
	class Date {
		int year;
		int month;
		int day;
		Status m_state;
		bool format;
		bool validate();
		int unique() const;
		int stringToInt(char* str);
		bool validDigit(char* str);
	public:
		Date();
		Date(int newYear, int newMonth, int newDay);
		~Date();
		Date(const Date&);
		Date& operator=(const Date&);
		bool operator==(const Date& obj) const;
		bool operator!=(const Date& obj) const;
		bool operator<(const Date& obj) const;
		bool operator>(const Date& obj) const;
		bool operator<=(const Date& obj) const;
		bool operator>=(const Date& obj) const;
		Status& state();
		Date& formatted(bool format);
		operator bool() const;
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& is);
	};
	std::ostream& operator<<(std::ostream& os, const Date& obj);
	std::istream& operator>>(std::istream& is, Date& obj);
};

#endif
