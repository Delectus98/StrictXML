
#include "TagDoc.h"

XmlType TagDoc::TYPE = XmlType::XML_TAG_DOC;

void TagDoc::setName(const std::string &value) {
    _name = value;
}

void TagDoc::removeAttribute(const std::string &attr) {
    throw XmlWrongSetException();
}

void TagDoc::setAttribute(const std::string &attr, const std::string &value) {
    throw XmlWrongSetException();
}

void TagDoc::setText(const std::string &value) {
    _line = value;
}

void TagDoc::addXml(std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException();
}

void TagDoc::removeXml(size_t index) {
    throw XmlWrongSetException();
}

void TagDoc::replaceXml(size_t index, std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException();
}

const std::string &TagDoc::getName() const {
    return _name;
}

const std::string &TagDoc::getAttributeValueOrElse(const std::string &attr, const std::string &other) const {
    throw XmlWrongGetException();
}

const std::string &TagDoc::getText() const {
    return _line;
}

size_t TagDoc::getXmlCount() const {
    throw XmlWrongGetException();
}

const Xml *TagDoc::getXml(size_t index) const {
    throw XmlWrongGetException();
}

Xml *TagDoc::getXml(size_t index) {
    throw XmlWrongGetException();
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
