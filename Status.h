//Ario Nazemirad
#ifndef STATUS_H
#define STATUS_H

namespace sdds {
	class Status {
		char* objStatus;
		int statusCode;
	public:
		Status();
		~Status();
		Status(const char* obj);
		Status& operator=(const Status&);
		Status& operator=(int newValue);
		Status& operator=(const char* newStatus);
		operator int() const;
		operator const char* () const;
		operator bool() const;
		Status& clear();
	};
	std::ostream& operator<<(std::ostream& os, const Status& obj);
};

#endif
