//
// Created by Maxime on 16/05/2018.
//

#include "TagComment.h"

XmlType TagComment::TYPE = XmlType::XML_TAG_COMMENT;

void TagComment::setName(const std::string &value) {
    throw XmlWrongSetException(TYPE, "XmlText can't use 'getText");
}

void TagComment::removeAttribute(const std::string &attr) {
    throw XmlWrongSetException(TYPE, "XmlText can't use 'removeAttribute");
}

void TagComment::setAttribute(const std::string &attr, const std::string &value) {
    throw XmlWrongSetException(TYPE, "XmlText can't use 'setAttribute");
}

void TagComment::setText(const std::string &value) {
    _comment = value;
}

void TagComment::addXml(std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException(TYPE, "TagComment can't use 'addXml");
}

void TagComment::removeXml(size_t index) {
    throw XmlWrongSetException(TYPE, "TagComment can't use 'removeXml");
}

void TagComment::replaceXml(size_t index, std::unique_ptr<Xml> xml) {
    throw XmlWrongSetException(TYPE, "TagComment can't use 'replaceXml");
}

const std::string &TagComment::getName() const{
    throw XmlWrongGetException(TYPE, "TagComment can't use 'getName");
}

const std::string &TagComment::getAttributeValueOrElse(const std::string &attr, const std::string &other) const{
    throw XmlWrongGetException(TYPE, "TagComment can't use 'getAttributeValueOrElse");
}

const std::string &TagComment::getText() const{
    return _comment;
}

size_t TagComment::getXmlCount() const{
    throw XmlWrongGetException(TYPE, "TagComment can't use 'getXmlCount");
}

const Xml *TagComment::getXml(size_t index) const {
    throw XmlWrongGetException(TYPE, "TagComment can't use 'getXml");
}

Xml *TagComment::getXml(size_t index) {
    throw XmlWrongGetException(TYPE, "TagComment can't use 'getXml");
}

const XmlType &TagComment::getType() const {
    return TYPE;
}

std::string TagComment::toString(const std::string& indent) const {
    return (indent + "<!--" + _comment + "-->");
}

bool TagComment::save(std::ofstream &stream, const std::string& indent) const {
    stream << this->toString(indent);
    return static_cast<bool>(stream);
}
