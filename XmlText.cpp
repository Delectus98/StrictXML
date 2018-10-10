
#include "XmlText.h"

XmlType XmlText::TYPE = XmlType::XML_TEXT;

void XmlText::setName(const std::string &value) {
    throw XmlWrongSetException();
}

void XmlText::removeAttribute(const std::string &attr) {
    throw XmlWrongSetException();
}

void XmlText::setAttribute(const std::string &attr, const std::string &value) {
    throw XmlWrongSetException();
}

void XmlText::setText(const std::string &value) {
    _content = value;
}

void XmlText::addXml(std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException();
}

void XmlText::removeXml(size_t index) {
    throw XmlWrongSetException();
}

void XmlText::replaceXml(size_t index, std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException();
}

const std::string &XmlText::getName() const{
    throw XmlWrongGetException();
}

const std::string &XmlText::getAttributeValueOrElse(const std::string &attr, const std::string &other) const{
    throw XmlWrongGetException();
}

const std::string &XmlText::getText() const{
    return _content;
}

size_t XmlText::getXmlCount() const{
    throw XmlWrongGetException();
}

const Xml *XmlText::getXml(size_t index) const {
    throw XmlWrongGetException();
}

Xml *XmlText::getXml(size_t index) {
    throw XmlWrongGetException();
}

const XmlType &XmlText::getType() const {
    return TYPE;
}

std::string XmlText::toString(const std::string& indent) const {
    return (indent + _content);
}

bool XmlText::save(std::ofstream &stream, const std::string& indent) const {
    stream << this->toString(indent);
    return static_cast<bool>(stream);
}
