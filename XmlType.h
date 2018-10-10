//
// Created by Maxime on 15/05/2018.
//

#ifndef KEYBOARDKNOCKOUT_XMLTYPE_H
#define KEYBOARDKNOCKOUT_XMLTYPE_H

#include <tuple>


enum XmlType : int{
    XML_TAG_REGULAR = 0, /*! OPENING TAG like <html> that need to be close by </html> somewhere after */
    XML_TAG_CLOSING = 1 << 0, /*! CLOSING TAG like </html> that need to be openned by <html> somewhere before */
    XML_TAG_SELFCLOSING = 1 << 1, /*! SELF CLOSING TAG like <html/> */
    XML_TAG_COMMENT = 1 << 2, /*! COMMENT TAG like <!-- commentay --> */
    XML_TAG_SCRIPT = 1 << 3, /*! SCRIPT TAG like <?php ?> */
    XML_TAG_DOC = 1 << 4, /*! DOC TAG like <!DOCTYPE> */

    XML_TEXT = 1 << 5,
    XML_UNKNOWN = 1 << 6

};


const std::pair<const std::string, const std::string> TAG_DEFINITION[6]  = {
        std::make_pair("<", ">"),
        std::make_pair("</", ">"),
        std::make_pair("<", "/>"),
        std::make_pair("<!--", "-->"),
        std::make_pair("<?", "?>"),
        std::make_pair("<!", ">")
};

const std::pair<const std::string, const std::string>& getDef(XmlType type);

XmlType defineXml(const std::string& tag);



#endif //KEYBOARDKNOCKOUT_XMLTYPE_H
