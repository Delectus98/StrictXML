
#include "TagScript.h"

XmlType TagScript::TYPE = XmlType::XML_TAG_SELFCLOSING;

void TagScript::setName(const std::string &value) {
    _name = value;
}

void TagScript::removeAttribute(const std::string &attr) {
    throw XmlWrongSetException();
}

void TagScript::setAttribute(const std::string &attr, const std::string &value) {
    throw XmlWrongSetException();
}

void TagScript::setText(const std::string &value) {
    _line = value;
}

void TagScript::addXml(std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException();
}

void TagScript::removeXml(size_t index) {
    throw XmlWrongSetException();
}

void TagScript::replaceXml(size_t index, std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException();
}

const std::string &TagScript::getName() const {
    return _name;
}

const std::string &TagScript::getAttributeValueOrElse(const std::string &attr, const std::string &other) const {
    throw XmlWrongGetException();
}

const std::string &TagScript::getText() const {
    return _line;
}

size_t TagScript::getXmlCount() const {
    throw XmlWrongGetException();
}

const Xml *TagScript::getXml(size_t index) const {
    throw XmlWrongGetException();
}

Xml *TagScript::getXml(size_t index) {
    throw XmlWrongGetException();
}

std::string TagScript::toString(const std::string& indent) const {
    return (indent + "<?" + _name + " " + _line + "?>");
}

const XmlType &TagScript::getType() const {
    return TYPE;
}

bool TagScript::save(std::ofstream &stream, const std::string& indent) const {
    stream << indent + "<?" + _line + "?>";
    return static_cast<bool>(stream);
}
