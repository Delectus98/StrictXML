
#include <iostream>
#include "Xml.h"
#include "XmlException.h"


XmlType defineXml(const std::string &tag) {
    if (tag.find('<') == 0) {
        if (tag.find("<!--") == 0 && tag.find("-->") == tag.size() - 3) {
            return XmlType::XML_TAG_COMMENT;
        } else if (tag.find("<?") == 0 && tag.find("?>") == tag.size() - 2) {
            return XmlType::XML_TAG_SCRIPT;
        } else if (tag.find("<!") == 0 && tag.find(">") == tag.size() - 1) {
            return XmlType::XML_TAG_DOC;
        } else if (tag.find("</") == 0 && tag.find(">") == tag.size() - 1) {
            return XmlType::XML_TAG_CLOSING;
        } else if (tag.find("<") == 0 && tag.find("/>") == tag.size() - 2) {
            return XmlType::XML_TAG_SELFCLOSING;
        } else if (tag.find("<") == 0 && tag.find(">") == tag.size() - 1) {
            return XmlType::XML_TAG_REGULAR;
        } else {
            return XmlType::XML_UNKNOWN;
        }
    } else {
        return XmlType::XML_TEXT;
    }
}



const std::pair<const std::string, const std::string>& getDef(XmlType type) {
    switch (type) {

        case XML_TAG_REGULAR: return TAG_DEFINITION[0];
        case XML_TAG_CLOSING: return TAG_DEFINITION[1];
        case XML_TAG_SELFCLOSING: return TAG_DEFINITION[2];
        case XML_TAG_COMMENT: return TAG_DEFINITION[3];
        case XML_TAG_SCRIPT: return TAG_DEFINITION[4];
        case XML_TAG_DOC:return TAG_DEFINITION[5];
        default: throw XmlCreationException(type, "Bad tag definition selection");
    }
}
