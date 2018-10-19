//
// Created by Maxime on 15/05/2018.
//

#ifndef XMLEXCEPTION_H
#define XMLEXCEPTION_H

#include <exception>
#include <iostream>
#include "XmlType.h"

class XmlException : public std::exception {
protected:
    const XmlType _type;
    const std::string _error;
protected:
    XmlException(const XmlType type, const std::string& error) : _type(type), _error(error) {}

    virtual ~XmlException() override {}
public:
    virtual const char* what() const noexcept {
        return _error.c_str();
    }

    virtual void print() const {
        std::cout << what() << std::endl;
    }
};

class XmlCreationException : public XmlException {
public:
    XmlCreationException(const XmlType type, const std::string& error) : XmlException(type, "Xml component creation error: "+error){}
};

class XmlWrongGetException : public XmlException {
public:
    XmlWrongGetException(const XmlType type, const std::string& error) : XmlException(type, "Wrong tentative of getting value: " + error){}
};

class XmlWrongSetException : public XmlException {
public:
    XmlWrongSetException(const XmlType type, const std::string& error) : XmlException(type, "Wrong tentative of getting value: "  + error){}
};

#endif //XMLEXCEPTION_H
