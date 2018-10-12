//
// Created by Maxime on 16/05/2018.
//

#ifndef XMLTEXT_H
#define XMLTEXT_H

#include <map>
#include "Xml.h"
#include "XmlException.h"

class XmlText : public Xml {
private:
    static XmlType TYPE;
    std::string _content;
public:
    XmlText() {}
    ~XmlText() override {}

    void setName(const std::string &value) override;

    void removeAttribute(const std::string &attr) override;

    void setAttribute(const std::string &attr, const std::string &value) override;

    void setText(const std::string &value) override;

    void addXml(std::unique_ptr<Xml> xml) override;

    void removeXml(size_t index) override;

    void replaceXml(size_t index, std::unique_ptr<Xml> xml) override;

    const std::string &getName() const override;

    bool isAttribute(const std::string& name) const override {
        throw XmlWrongGetException(TYPE, "XmlText can't use 'isAttribute");
    }

    const std::string &getAttributeValueOrElse(const std::string &attr, const std::string &other) const override;

    const std::string &getText() const override;

    size_t getXmlCount() const override;

    const Xml *getXml(size_t index) const override;

    Xml *getXml(size_t index) override;

    std::string toString(const std::string& indent) const override;

    bool save(std::ofstream &stream, const std::string& indent) const override;

    const XmlType &getType() const override;

};


#endif //XMLTEXT_H
