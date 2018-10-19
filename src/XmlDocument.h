//
// Created by Maxime on 16/05/2018.
//

#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

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


class XmlDocument {
private:
    static std::unique_ptr<Xml> createTag(const std::string &data);

    std::deque<std::unique_ptr<Xml>> _xmls;
    std::string _msgError;
public:
    //int loadFromMemory(const std::string& data) {}

    int loadFromFile(const std::string &filePath);

    const std::string getError() const {
        return _msgError;
    }

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

};



#endif //XMLDOCUMENT_H
