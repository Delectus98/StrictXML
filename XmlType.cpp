
#include <iostream>
#include "Xml.h"
#include "XmlException.h"


XmlType defineXml(const std::string &tag) {
    if (tag.find('<') != std::string::npos) {
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

        case XML_TAG_REGULAR: return TAG_DEFINITION[0]; break;
        case XML_TAG_CLOSING: return TAG_DEFINITION[1]; break;
        case XML_TAG_SELFCLOSING: return TAG_DEFINITION[2];  break;
        case XML_TAG_COMMENT: return TAG_DEFINITION[3]; break;
        case XML_TAG_SCRIPT: return TAG_DEFINITION[4]; break;
        case XML_TAG_DOC:return TAG_DEFINITION[5]; break;
        default: std::cerr << "Bag tag definition selection" << std::endl; throw XmlException();  break;
    }
}
