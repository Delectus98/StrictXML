//
// Created by Maxime on 15/05/2018.
//

#ifndef KEYBOARDKNOCKOUT_TAGREGULAR_H
#define KEYBOARDKNOCKOUT_TAGREGULAR_H

#include <deque>
#include <map>
#include "Xml.h"
#include "XmlType.h"
#include "XmlException.h"


class TagRegular : public Xml{
private:
    static XmlType TYPE;
    std::string _name;
    std::deque<std::unique_ptr<Xml>> _xmls;
    std::map<std::string,std::string> _attributes;
public:
    explicit TagRegular() = default;
    ~TagRegular() override = default;

    void setName(const std::string &value) override;

    void removeAttribute(const std::string &attr) override;

    void setAttribute(const std::string &attr, const std::string &value) override;

    void setText(const std::string &value) override;

    void addXml(std::unique_ptr<Xml> xml) override;

    void removeXml(size_t index) override;

    void replaceXml(size_t index, std::unique_ptr<Xml> xml) override;

    const std::string &getName() const override;

    bool isAttribute(const std::string& name) const override {
        return _attributes.find(name) != _attributes.end();
    }

    const std::string &getAttributeValueOrElse(const std::string &attr, const std::string &other) const override;

    const std::string &getText() const override;

    size_t getXmlCount() const override;

    const Xml *getXml(size_t index) const override;

    Xml *getXml(size_t index) override;

    std::string toString(const std::string& indent) const override;

    bool save(std::ofstream &stream, const std::string& indent) const override;

    const XmlType &getType() const override;

public:

};


#endif //KEYBOARDKNOCKOUT_TAGREGULAR_H
