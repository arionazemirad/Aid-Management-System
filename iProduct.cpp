//Ario Nazemirad
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "iProduct.h"
using namespace std;
namespace sdds {
	iProduct::~iProduct() {
	}

	std::ostream& operator<<(std::ostream& ostr, const iProduct& obj) {
		obj.display(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, iProduct& obj) {
		obj.read(istr);
		return istr;
	}
}
