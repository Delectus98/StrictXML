//
// Created by Maxime on 16/05/2018.
//

#include "TagSelfClosing.h"

XmlType TagSelfClosing::TYPE = XmlType::XML_TAG_SELFCLOSING;

void TagSelfClosing::setName(const std::string &value) {
    _name = value;
}

void TagSelfClosing::removeAttribute(const std::string &attr) {
    _attributes.erase(attr);
}

void TagSelfClosing::setAttribute(const std::string &attr, const std::string &value) {
    _attributes[attr] = value;
}

void TagSelfClosing::setText(const std::string &value) {
    throw XmlWrongSetException(TYPE, _name + " can't use 'setText");
}

void TagSelfClosing::addXml(std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException(TYPE, _name + " can't use 'addXml");
}

void TagSelfClosing::removeXml(size_t index) {
    throw XmlWrongSetException(TYPE, _name + " can't use 'removeXml");
}

void TagSelfClosing::replaceXml(size_t index, std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException(TYPE, _name + " can't use 'replaceXml");
}

const std::string &TagSelfClosing::getName() const{
    return _name;
}

const std::string &TagSelfClosing::getAttributeValueOrElse(const std::string &attr, const std::string &other) const{
    auto itr = _attributes.find(attr);
    if (itr != _attributes.end()) {
        return itr->second;
    } else {
        return other;
    }
}

const std::string &TagSelfClosing::getText() const{
    throw XmlWrongGetException(TYPE, _name + " can't use 'getText");
}

size_t TagSelfClosing::getXmlCount() const{
    throw XmlWrongGetException(TYPE, _name + " can't use 'getXmlCount");
}

const Xml *TagSelfClosing::getXml(size_t index) const {
    throw XmlWrongGetException(TYPE, _name + " can't use 'getXml");
}

Xml *TagSelfClosing::getXml(size_t index) {
    throw XmlWrongGetException(TYPE, _name + " can't use 'getXml");
}

const XmlType &TagSelfClosing::getType() const {
    return TYPE;
}

std::string TagSelfClosing::toString(const std::string& indent) const {
    std::string temp =  indent + "<" + _name + " ";
    for (auto itr = _attributes.begin() ; itr != _attributes.end() ; ++itr) {
        temp += itr->first + "=\"" + itr->second + "\" ";
    }
    return (temp + "/>");
}

bool TagSelfClosing::save(std::ofstream &stream, const std::string& indent) const {
    stream << this->toString(indent);
    return static_cast<bool>(stream);
}
