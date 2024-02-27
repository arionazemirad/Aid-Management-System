//Ario Nazemirad
#ifndef PERISHABLE_H
#define PERISHABLE_H
#include "Item.h"
#include "Date.h"

namespace sdds {
	class Perishable : public Item {
		char* m_handling;
		Date m_expiry;
	public:
		Perishable();
		~Perishable();
		Perishable(const Perishable&);
		Perishable& operator=(const Perishable&);
		Date& expiry();
		int readSku(std::istream& istr);
		std::ofstream& save(std::ofstream& ofstr) const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};
}

#endif
