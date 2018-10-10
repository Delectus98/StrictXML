//
// Created by Maxime on 15/05/2018.
//

#include "TagRegular.h"

XmlType TagRegular::TYPE = XmlType::XML_TAG_REGULAR;

void TagRegular::setName(const std::string &value) {
    _name = value;
}

void TagRegular::removeAttribute(const std::string &attr) {
    _attributes.erase(attr);
}

void TagRegular::setAttribute(const std::string &attr, const std::string &value) {
    _attributes[attr] = value;
}

void TagRegular::setText(const std::string &value) {
    throw XmlWrongSetException();
}

void TagRegular::addXml(std::unique_ptr<Xml> xml) {
    _xmls.push_back(std::move(xml));
}

void TagRegular::removeXml(size_t index) {
    _xmls.erase(_xmls.begin()+index);
}

void TagRegular::replaceXml(size_t index, std::unique_ptr<Xml> xml) {
    _xmls[index] = std::move(xml);
}

const std::string &TagRegular::getName() const {
    return _name;
}

const std::string &TagRegular::getAttributeValueOrElse(const std::string &attr, const std::string &other) const {
    auto itr = _attributes.find(attr);
    if (itr != _attributes.end()) {
        return itr->second;
    } else {
        return other;
    }
}

const std::string &TagRegular::getText() const {
    throw XmlWrongSetException();
}

size_t TagRegular::getXmlCount() const {
    return _xmls.size();
}

const Xml *TagRegular::getXml(size_t index) const {
    if (index < _xmls.size()) return _xmls.operator[](index).get();
    else return nullptr;
}

Xml *TagRegular::getXml(size_t index) {
    if (index < _xmls.size()) return _xmls.operator[](index).get();
    else return nullptr;
}

const XmlType &TagRegular::getType() const {
    return TYPE;
}

std::string TagRegular::toString(const std::string& indent) const {
    std::string temp = indent + "<" + _name + "> ";
    for (auto itr = _attributes.begin() ; itr != _attributes.end() ; ++itr) {
        temp += itr->first + "=\"" + itr->second + "\" ";
    }
    for (auto itr = _xmls.begin() ; itr != _xmls.end() ; ++itr) {
        temp += "\n" + itr.operator*()->toString(indent + indent);
    }
    return temp + "\n" + indent + "</" + _name + ">";
}

bool TagRegular::save(std::ofstream &stream, const std::string& indent) const {
    stream << this->toString(indent);
    return static_cast<bool>(stream);
}
