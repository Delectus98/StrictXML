
#include <stack>
#include <iostream>
#include "XmlDocument.h"

#define _ATTRIBUT_XML_ '\"'
#define _BACKSLASH_XML_ '\\'
#define _SPACE_XML_ ' '
#define _CHEVRON_OUVERT_XML_ '<'
#define _CHEVRON_FERME_XML_ '>'

int XmlDocument::loadFromFile(const std::string &filePath) {
    std::ifstream stream;
    stream.open(filePath.c_str(), std::ios::in);

    if (stream) {
        ///SEPARATING XML DYNAMICALLY
        std::queue<std::string> tagPrintStack;
        size_t tagNumber = 0;

        try {
            size_t lineCount = 0;
            std::string line;
            std::string current;
            bool tag = false;
            bool eclipse = false; ///when we meet char '\' like in c++
            bool attribute = false;

            while (std::getline(stream, line)) {
                lineCount += 1;

                for (size_t i(0); i < line.size(); ++i) {
                    if (line[i] < 32) continue;

                    if (eclipse) {
                        eclipse = false;
                        current += line[i];
                    } else if (attribute) {
                        switch (line[i]) {
                            case _ATTRIBUT_XML_: {
                                attribute = false;
                                current += _ATTRIBUT_XML_;
                            }
                                break;
                            default:
                                current += line[i];
                                break;
                        }
                    } else {
                        switch (line[i]) {
                            case _BACKSLASH_XML_: {
                                eclipse = true;
                            } break;
                            case _ATTRIBUT_XML_: {
                                attribute = true;
                                current += _ATTRIBUT_XML_;
                            } break;
                            case _SPACE_XML_: {
                                if (!current.empty() && current[current.size() - 1] != _SPACE_XML_) {
                                    current += _SPACE_XML_;
                                } else {
                                    continue;
                                }
                            } break;
                            case _CHEVRON_OUVERT_XML_: {
                                if (tag) {
                                    _msgError = "Can't open a tag inside a tag at line " + std::to_string(lineCount);
                                    return 0;
                                }

                                tag = true;

                                if (current.empty()) {
                                    current += _CHEVRON_OUVERT_XML_;
                                } else {
                                    ///@TEST ADDING NEW XML @TEST
                                    if (!current.empty()) {
                                        tagPrintStack.push(current);
                                        current.clear();
                                    }
                                    current += _CHEVRON_OUVERT_XML_;
                                }
                            } break;
                            case _CHEVRON_FERME_XML_: {
                                ///@TEST ADDING NEW XML @TEST
                                if (tag == false) {
                                    _msgError = "Can't close a non-existing opening tag at line"  + std::to_string(lineCount);
                                    return 0;
                                }

                                tag = false;
                                current += _CHEVRON_FERME_XML_;
                                tagPrintStack.push(current);
                                current.clear();
                            } break;
                            default:
                                current += line[i];
                                break;
                        }
                    }
                }
            }
            stream.close();

            ///NE PAS OUBLIER DE METTRE CURRENT DANS LE STACK SI IL NEST PAS VU (pour seulement les textes)


            ///CREATING TAGS
            ///CURRENT BRANCH est une queue contenant la racine actuelle (la racine est un TAG_REGULAR)
            ///QUAND ON ARRIVE A UN NOUVEAU TAG REGULAR ON L'AJOUTE A LA PILE POUR AJOUTER LES BON TAGS
            ///LORSQU'ON ARRIVE A UN TAG CLOSING ON ENLEVE LE DERNIERE ELEMENT DE LA PILE
            std::deque<std::unique_ptr<Xml>> currentBranche;
            while (!tagPrintStack.empty()) {
                if (!tagPrintStack.front().empty()) {
                    auto uniqueXml = this->createTag(tagPrintStack.front());
                    switch (uniqueXml->getType()) {
                        case XML_TAG_REGULAR: {
                            currentBranche.push_front(std::move(uniqueXml)); //move current xml (first) to branches end (newest)
                        } break;
                        case XML_TAG_CLOSING: {
                            if (!currentBranche.empty() && uniqueXml->getName() == currentBranche.front()->getName()) {
                                ///on arrive a la fin d'un tag ouvrant

                                ///lower tag (le tag a la fin de pile)
                                auto temp = std::move(currentBranche.front());
                                currentBranche.pop_front();

                                ///upper tag (le tag qui étant avant dernier dans la pile mais maintenant dernier)
                                if (currentBranche.empty()) {
                                    _xmls.push_back(std::move(temp));
                                } else {
                                    currentBranche.front()->addXml(std::move(temp));
                                }
                            } else {
                                _msgError = "wrong closing tag name (missing tag). | Xml: " + std::to_string(tagNumber);
                                return 0;
                            }
                        } break;
                        default: {
                            if (currentBranche.empty()) {
                                _xmls.push_back(std::move(uniqueXml));
                            } else {
                                currentBranche.front()->addXml(std::move(uniqueXml));
                            }
                        } break;
                    }
                }

                tagPrintStack.pop();
                tagNumber += 1;
            }

            //mettre le dernier truc qui est dans le xmlStack dans la document
            if (currentBranche.size() == 1) {
                _xmls.push_back(std::move(currentBranche.front()));
                currentBranche.pop_front();
            }

            if (!currentBranche.empty()) {
                _msgError = "missing closing tag after currentBranche.top()->toString(). |  Xml:" + std::to_string(tagNumber);
                return 0;
            }

            return 1;
        } catch (const XmlException& ex) {
            stream.close();
            _msgError = std::string(ex.what()) + " | Xml:" + std::to_string(tagNumber);
            return 0;
        }
    } else {
        _msgError = "The file '" + filePath + "' do not exist.";
        return -1;
    }

}

std::unique_ptr<Xml> XmlDocument::createTag(const std::string &data) {
    //if (data.length() != 0) {
        XmlType xmlType = defineXml(data);
        std::unique_ptr<Xml> smart = nullptr;
        switch (xmlType) {
            case XML_TAG_REGULAR: smart = std::unique_ptr<Xml>(new TagRegular()); break;
            case XML_TAG_CLOSING: smart = std::unique_ptr<Xml>(new TagClosing()); break;
            case XML_TAG_SELFCLOSING: smart = std::unique_ptr<Xml>(new TagSelfClosing()); break;
            case XML_TAG_COMMENT: smart = std::unique_ptr<Xml>(new TagComment()); break;
            case XML_TAG_SCRIPT: smart = std::unique_ptr<Xml>(new TagScript()); break;
            case XML_TAG_DOC: smart = std::unique_ptr<Xml>(new TagDoc()); break;
            case XML_TEXT: smart = std::unique_ptr<Xml>(new XmlText()); break;
            default: throw XmlCreationException(xmlType, "Unknown type of tag");
        }

        if (xmlType == XML_TAG_REGULAR || xmlType == XML_TAG_SELFCLOSING || xmlType == XML_TAG_CLOSING) {
            std::string temp = std::string(
                    data.begin() + getDef(xmlType).first.length(),
                    data.begin() + data.length() - getDef(xmlType).second.length()
            );
            ////GENERATE HEAD XML
            std::string undefinedName;
            std::string undefinedAttName;
            std::string undefinedAttValue;
            bool named = false;
            bool comment = false;
            for (size_t i(0) ; i < temp.length() ; ++i) {
                if (!named) {
                    //si c'est un nom (le premier est le nom)
                    switch (temp[i]) {
                        case ' ': case '/': {
                            if (undefinedName.length() == 0) {
                                ///alors on a eu que des ' ' et on accepte les ' ' en trop
                            } else {
                                named = true;
                            }
                        }break;

                        case '=':case '"':case '<':case '>': {
                            throw XmlCreationException(xmlType, "Tag name can't contain special chars like (=, <, >, ...)");
                        } break;

                        default:
                            undefinedName += temp[i];
                            break;
                    }
                } else {
                    /// si c'est un attribut
                    if (!comment) {
                        ///si on n'est pas dans le commentaire
                        switch (temp[i]) {
                            case '=': {
                                if (undefinedAttName.length() == 0) {
                                    throw XmlCreationException(xmlType, "Attribute must be named");
                                } else {
                                    if (i + 1 < temp.length() && temp[i + 1] == '"') {
                                        comment = true;
                                        i++;
                                    } else {
                                        throw XmlCreationException(xmlType, "'=' symbol must be near of attribute value");
                                    }
                                }
                            } break;

                            case ' ': {//cassure de l'attribut
                                if (undefinedAttName.length()!=0) {
                                    throw XmlCreationException(xmlType, "'=' symbol must be near of attribute name");
                                }
                            } break;

                                //charactères non toléré
                            case '/':case '<':case '>': {
                                throw XmlCreationException(xmlType, "Tag head can't contain special chars like (/, =, <, >, ...)");
                            } break;

                            default: undefinedAttName += temp[i]; break;
                        }
                    } else {
                        ///si on est dans le commentaire
                        switch (temp[i]) {
                            case '"': {
                                smart->setAttribute(undefinedAttName, undefinedAttValue);

                                undefinedAttName.clear();
                                undefinedAttValue.clear();
                                comment = false;
                            } break;

                            default:
                                undefinedAttValue += temp[i];
                                break;
                        }
                    }
                }
            }
            smart->setName(undefinedName);

            ////END GENERATE HEAD XML
        } else if(xmlType == XML_TAG_COMMENT || xmlType == XML_TAG_SCRIPT || xmlType == XML_TAG_DOC) {
            std::string temp = std::string(
                    data.begin() + getDef(xmlType).first.length(),
                    data.begin() + data.length() - getDef(xmlType).second.length()
            );
            size_t spacePos = temp.find(' ', 0);

            smart->setName(std::string(temp.begin(), temp.begin() + spacePos));
            smart->setText(std::string(temp.begin() + spacePos + 1, temp.end()));
        } else if(xmlType == XML_TEXT) {
            smart->setText(data);
        } else {
            throw XmlCreationException(xmlType, "Bad tag type creation");
        }

        return std::move(smart);
    /*} else {
        ///BAD XML LENGTH EXCEPTION
        std::cerr << "wait what bad length xml exception?" << std::endl;
        throw XmlException();
    }*/
}
