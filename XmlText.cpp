
#include "XmlText.h"

XmlType XmlText::TYPE = XmlType::XML_TEXT;

void XmlText::setName(const std::string &value) {
    throw XmlWrongSetException(TYPE, "XmlText can't use 'setName");
}

void XmlText::removeAttribute(const std::string &attr) {
    throw XmlWrongSetException(TYPE, "XmlText can't use 'removeAttribute");
}

void XmlText::setAttribute(const std::string &attr, const std::string &value) {
    throw XmlWrongSetException(TYPE, "XmlText can't use 'setAttribute");
}

void XmlText::setText(const std::string &value) {
    _content = value;
}

void XmlText::addXml(std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException(TYPE, "XmlText can't use 'addXml");
}

void XmlText::removeXml(size_t index) {
    throw XmlWrongSetException(TYPE, "XmlText can't use 'removeXml");
}

void XmlText::replaceXml(size_t index, std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException(TYPE, "XmlText can't use 'replaceXml");
}

const std::string &XmlText::getName() const{
    throw XmlWrongGetException(TYPE, "XmlText can't use 'getName");
}

const std::string &XmlText::getAttributeValueOrElse(const std::string &attr, const std::string &other) const{
    throw XmlWrongGetException(TYPE, "XmlText can't use 'getAttributeValueOrElse");
}

const std::string &XmlText::getText() const{
    return _content;
}

size_t XmlText::getXmlCount() const{
    throw XmlWrongGetException(TYPE, "XmlText can't use 'getXmlCount");
}

const Xml *XmlText::getXml(size_t index) const {
    throw XmlWrongGetException(TYPE, "XmlText can't use 'getXml");
}

Xml *XmlText::getXml(size_t index) {
    throw XmlWrongGetException(TYPE, "XmlText can't use 'getXml");
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
