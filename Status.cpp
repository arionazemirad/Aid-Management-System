//Ario Nazemirad
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Status.h"

using namespace std;
namespace sdds {
    Status::Status() {
        objStatus = nullptr;
        statusCode = 0;
    }

    Status::Status(const char* obj) {
        statusCode = 0;
        if (obj != nullptr) {
            objStatus = new char[strlen(obj) + 1];
            strcpy(objStatus, obj);
        }
    }

    Status::~Status() {
        delete[] objStatus;
    }

    Status& Status::operator=(const Status& source) {
        if (this != &source) {
            statusCode = source.statusCode;
            delete[] objStatus;

            if (source.objStatus != nullptr) {
                objStatus = new char[strlen(source.objStatus) + 1];
                strcpy(objStatus, source.objStatus);
            }
            else {
                objStatus = nullptr;
            }
        }
        return *this;
    }

    Status& Status::operator=(int newValue) {
        statusCode = newValue;
        return *this;
    }

    Status& Status::operator=(const char* newStatus) {
        if (newStatus != nullptr) {
            objStatus = new char[strlen(newStatus) + 1];
            strcpy(objStatus, newStatus);
        }
        return *this;
    }

    Status::operator int() const {
        return statusCode;
    }

    Status::operator const char* () const {
        return objStatus;
    }

    Status::operator bool() const {
        return objStatus == nullptr;
    }

    Status& Status::clear() {
        statusCode = 0;
        if (objStatus != nullptr) {
            delete[] objStatus;
            objStatus = nullptr;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Status& obj) {
        if (obj || int(obj) != 0) {
            os << "ERR#" << int(obj) << ": " << (const char*)(obj);
        }
        else {
            os << (const char*)(obj);
        }
        return os;
    }
};
