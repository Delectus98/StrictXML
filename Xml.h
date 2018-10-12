
#ifndef XML_H
#define XML_H

#include <string>
#include <memory>
#include <fstream>
#include "XmlType.h"

/*
class TagRegular;
class TagClosing;
class TagSelfClosing;
class TagComment;
class TagScript;
class TagDoc;
class XmlText;*/


class Xml {
public:
    Xml() = default;
    virtual ~Xml() = default;

    virtual const XmlType& getType() const = 0;

    ///Setters
    virtual void setName(const std::string& value) = 0;

    virtual void removeAttribute(const std::string& attr) = 0;

    virtual void setAttribute(const std::string& attr, const std::string& value) = 0;

    virtual void setText(const std::string& value) = 0;

    virtual void addXml(std::unique_ptr<Xml> xml) = 0;

    virtual void removeXml(size_t index) = 0;

    virtual void replaceXml(size_t index, std::unique_ptr<Xml> xml) = 0;

    ///Getters
    virtual const std::string& getName() const = 0;

    virtual bool isAttribute(const std::string& name) const = 0;

    virtual const std::string& getAttributeValueOrElse(const std::string& attr, const std::string& other) const = 0;

    virtual const std::string& getText() const = 0;

    virtual size_t getXmlCount() const = 0;

    virtual const Xml* getXml(size_t index) const = 0;

    virtual Xml* getXml(size_t index) = 0;

    virtual std::string toString(const std::string& indent) const = 0;

    virtual bool save(std::ofstream& stream, const std::string& indent) const = 0;

};


#endif //XML_H
