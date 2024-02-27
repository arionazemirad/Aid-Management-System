//Ario Nazemirad
#ifndef AIDMAN_H
#define AIDMAN_H
#include "Menu.h"
#include "iProduct.h"
namespace sdds {
	const int sdds_max_num_items = 100;
	class AidMan {
		char* fileName;
		Menu mainMenu;
		iProduct* iProductPointers[sdds_max_num_items];
		int numOfItems;
		int menu() const;
		void saveData();
		void dallocateData();
		bool loadData();
		void allocateAndCopy(const char* file);
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void addItem();
		void remove(int index);
		void removeItem();
		void updateQuantity();
		void sort();
		void shipItems();
	public:
		AidMan(const char* file = nullptr);
		~AidMan();
		void run();
	};
}

#endif
