//Ario Nazemirad
#ifndef MENU_H
#define MENU_H

namespace sdds {
	const int maxOptions = 15;
	class Menu {
		char* menuContent;
	public:
		Menu(const char* options = nullptr);
		~Menu();
		int run() const;
	};
}

#endif
