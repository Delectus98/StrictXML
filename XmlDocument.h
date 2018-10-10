//
// Created by Maxime on 16/05/2018.
//

#ifndef KEYBOARDKNOCKOUT_XMLDOCUMEN_H
#define KEYBOARDKNOCKOUT_XMLDOCUMEN_H

#include <fstream>
#include <memory>
#include <queue>
#include "XmlException.h"
#include "Xml.h"
#include "TagRegular.h"
#include "TagClosing.h"
#include "TagSelfClosing.h"
#include "TagComment.h"
#include "TagScript.h"
#include "TagDoc.h"
#include "XmlText.h"

#define _ATTRIBUT_XML_ '\"'
#define _BACKSLASH_XML_ '\\'
#define _SPACE_XML_ ' '
#define _CHEVRON_OUVERT_XML_ '<'
#define _CHEVRON_FERME_XML_ '>'

class XmlDocument {
private:
    static std::unique_ptr<Xml> createTag(const std::string &data);

    std::deque<std::unique_ptr<Xml>> _xmls;
public:
    //int loadFromMemory(const std::string& data) {}

    int loadFromFile(const std::string &filePath);

    size_t getXmlCount() const {
        return _xmls.size();
    }

    Xml* getXml(size_t index) {
        if (index < _xmls.size()) return _xmls.operator[](index).get();
        else return nullptr;
    }

    const Xml* const getCXml(size_t index) const {
        if (index < _xmls.size()) return _xmls.operator[](index).get();
        else return nullptr;
    }

    void print(const std::string& indent) const {
        for (auto itr = _xmls.begin() ; itr != _xmls.end() ; ++itr) {
            std::cout << itr.operator*()->toString(indent) << std::endl;
        }
    }

    //void put<XmlTag>()

};



#endif //KEYBOARDKNOCKOUT_XMLDOCUMEN_H
