#include "TagClosing.h"



XmlType TagClosing::TYPE = XmlType::XML_TAG_CLOSING;



void TagClosing::setName(const std::string &value) {
    _name = value;
}

void TagClosing::removeAttribute(const std::string &attr) {
    throw XmlWrongSetException();
}

void TagClosing::setAttribute(const std::string &attr, const std::string &value) {
    throw XmlWrongSetException();
}

void TagClosing::setText(const std::string &value) {
    throw XmlWrongSetException();
}

void TagClosing::addXml(std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException();
}

void TagClosing::removeXml(size_t index) {
    throw XmlWrongSetException();
}

void TagClosing::replaceXml(size_t index, std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException();
}

const std::string &TagClosing::getName() const{
    return _name;
}

const std::string &TagClosing::getAttributeValueOrElse(const std::string &attr, const std::string &other) const{
    throw XmlWrongGetException();

}

const std::string &TagClosing::getText() const{
    throw XmlWrongSetException();
}

size_t TagClosing::getXmlCount() const{
    throw XmlWrongGetException();
}

const Xml *TagClosing::getXml(size_t index) const {
    throw XmlWrongGetException();
}

Xml *TagClosing::getXml(size_t index) {
    throw XmlWrongGetException();
}

const XmlType &TagClosing::getType() const {
    return TYPE;
}

std::string TagClosing::toString(const std::string& indent) const {
    return (indent + "</" + _name + ">");
}

bool TagClosing::save(std::ofstream &stream, const std::string& indent) const {
    stream << this->toString(indent);
    return static_cast<bool>(stream);
}
