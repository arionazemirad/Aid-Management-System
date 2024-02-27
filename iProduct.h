/*
Name: Ario Nazemirad
Email: anazemirad@myseneca.ca
ID: 144647299
Date: Dec 3
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef IPRODUCT_H
#define IPRODUCT_H
namespace sdds {
	class iProduct {
	public:
		virtual ~iProduct();
		virtual int readSku(std::istream& istr) = 0;
		virtual int operator-=(int qty) = 0;
		virtual int operator+=(int qty) = 0;
		virtual operator double()const = 0;
		virtual operator bool()const = 0;
		virtual int qtyNeeded()const = 0;
		virtual int qty()const = 0;
		virtual void linear(bool isLinear) = 0;
		virtual std::ofstream& save(std::ofstream& ofstr)const = 0;
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;
		virtual std::ostream& display(std::ostream& ostr)const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual bool operator==(int sku)const = 0;
		virtual bool operator==(const char* description)const = 0;
	};
	std::ostream& operator<<(std::ostream& ostr, const iProduct& obj);
	std::istream& operator>>(std::istream& istr, iProduct& obj);
}

#endif