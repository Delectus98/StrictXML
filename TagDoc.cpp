
#include "TagDoc.h"

XmlType TagDoc::TYPE = XmlType::XML_TAG_DOC;

void TagDoc::setName(const std::string &value) {
    _name = value;
}

void TagDoc::removeAttribute(const std::string &attr) {
    throw XmlWrongSetException(TYPE, _name + " can't use 'removeAttribute");
}

void TagDoc::setAttribute(const std::string &attr, const std::string &value) {
    throw XmlWrongSetException(TYPE, _name + " can't use 'setAttribute");
}

void TagDoc::setText(const std::string &value) {
    _line = value;
}

void TagDoc::addXml(std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException(TYPE, _name + " can't use 'addXml");
}

void TagDoc::removeXml(size_t index) {
    throw XmlWrongSetException(TYPE, _name + " can't use 'removeXml");
}

void TagDoc::replaceXml(size_t index, std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException(TYPE, _name + " can't use 'replaceXml");
}

const std::string &TagDoc::getName() const {
    return _name;
}

const std::string &TagDoc::getAttributeValueOrElse(const std::string &attr, const std::string &other) const {
    throw XmlWrongGetException(TYPE, _name + " can't use 'getAttributeValueOrElse");
}

const std::string &TagDoc::getText() const {
    return _line;
}

size_t TagDoc::getXmlCount() const {
    throw XmlWrongGetException(TYPE, _name + " can't use 'getXmlCount");
}

const Xml *TagDoc::getXml(size_t index) const {
    throw XmlWrongGetException(TYPE, _name + " can't use 'getXml");
}

Xml *TagDoc::getXml(size_t index) {
    throw XmlWrongGetException(TYPE, _name + " can't use 'getXml");
}

std::string TagDoc::toString(const std::string& indent) const {
    return (indent + "<!" + _name + (_line.empty() ? "" : " " + _line) + ">");
}

const XmlType &TagDoc::getType() const {
    return TYPE;
}

bool TagDoc::save(std::ofstream &stream, const std::string& indent) const {
    stream << this->toString(indent);
    return static_cast<bool>(stream);
}
