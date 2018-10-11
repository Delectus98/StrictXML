//
// Created by Maxime on 15/05/2018.
//

#ifndef KEYBOARDKNOCKOUT_XMLEXCEPTION_H
#define KEYBOARDKNOCKOUT_XMLEXCEPTION_H

#include <exception>
#include <iostream>

class XmlException : public std::exception{
public:
    virtual void print() const{
        std::cerr << "XmlException" << std::endl;
    }
};

class XmlWrongGetException : public XmlException {
public:
    /*explicit XmlWrongGetException(const Xml* xml, const std::string& funName){
        xml->getType() 
    }*/
    
    virtual void print() const override {
        std::cerr << "XmlWrongGetException : can't use " + funName + "" << std::endl;
    }
};

class XmlWrongSetException : public XmlException {
public:
    virtual void print() const override {
        std::cerr << "XmlWrongSetException" << std::endl;
    }
};

#endif //KEYBOARDKNOCKOUT_XMLEXCEPTION_H
