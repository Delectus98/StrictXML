//
// Created by Maxime on 16/05/2018.
//

#include <iostream>
#include "XmlParser.h"


XmlParser::XmlParser(const Xml *xml) {
    _stack.push(std::make_pair(0, xml));
}

size_t XmlParser::length() const {
    return _stack.size();
}

XmlParser::operator bool() {
    return !_stack.empty();
}

const Xml* XmlParser::current() const{
    return _stack.top().second;
}

bool XmlParser::previous() {
    if (_stack.size() > 1) {
        size_t temp = _stack.top().first;
        _stack.pop();

        if (temp != 0) {
            _stack.push(std::make_pair(temp - 1, _stack.top().second->getXml(static_cast<size_t>(temp - 1))));
            return true;
        }
    }

    return false;
}

bool XmlParser::next() {
    if (_stack.size() > 1) {
        int temp = _stack.top().first;

        _stack.pop();

        if (temp + 1 < _stack.top().second->getXmlCount()) {
            _stack.push(std::make_pair(temp+1, _stack.top().second->getXml(static_cast<size_t>(temp+1))));
            return true;
        }
    }

    return false;
}

size_t XmlParser::paths() {
    if (_stack.size() != 0) {
        if (_stack.top().second->getType() == XmlType::XML_TAG_REGULAR) {
            return _stack.top().second->getXmlCount();
        }
    }

    return 0;
}

bool XmlParser::forward(int path) {
    if (_stack.size() != 0) {
        if (_stack.top().second->getType() == XmlType::XML_TAG_REGULAR) {
            _stack.push(std::make_pair(path, _stack.top().second->getXml(path)));
            return true;
        }

    }

    return false;
}

bool XmlParser::backward() {
    if (_stack.size() > 1) {
        _stack.pop();
        return true;
    } return false;
}

bool XmlParser::forwardAll() {
    if (_stack.size() != 0) {
        if (_stack.top().second->getType() == XmlType::XML_TAG_REGULAR && _stack.top().second->getXmlCount() != 0) {
            ///On plonge car il y a un chemin à parcourrir
            _stack.push(std::make_pair(0, _stack.top().second->getXml(0)));
        } else {
            ///Il n'y a pas de chemin a parcourrir
            if (_stack.size() != 1) {
                auto pathPos = _stack.top().first;
                _stack.pop();

                ///on cherche un chemin a droite en remontant
                while (_stack.size() != 0 && pathPos + 1 >= _stack.top().second->getXmlCount()) {
                    pathPos = _stack.top().first;
                    if (_stack.size() != 1) {
                        _stack.pop();
                    } else {
                        ///C'est le dernier noeud on ne peut pas aller plus loin (ou le seul)
                        return false;
                    }
                }

                ///si on trouve un chemin a droite suivant a parcourrir
                if (_stack.size() != 0 && pathPos + 1 < _stack.top().second->getXmlCount()) {
                    _stack.push(std::make_pair(pathPos + 1, _stack.top().second->getXml(pathPos + 1)));
                }
            } else {
                ///C'est le dernier noeud on ne peut pas aller plus loin (ou le seul)
                return false;
            }
        }
    } else {
        ///il n'y a plus rien a parcourrir
        return false;
    }


    return (_stack.size() != 0);
}

bool XmlParser::backwardAll() {
    if (_stack.size() != 0) {
        auto temp = _stack.top().first;
        _stack.pop();

        if (!_stack.empty()) {
            switch ((int)temp - 1) {
                case -1: return true; ///no left brother(s)
                default: {
                    ///on va au frère gauche puis au descendant le plus en base a droite
                    _stack.push(std::make_pair(temp - 1, _stack.top().second->getXml(temp - 1)));

                    auto pair = _stack.top();//.second->getXml(temp - 1);
                    while (pair.second->getType() == XmlType::XML_TAG_REGULAR && pair.second->getXmlCount() != 0) {
                        _stack.push(std::make_pair(pair.second->getXmlCount()-1, pair.second->getXml(pair.second->getXmlCount()-1)));
                        pair = _stack.top();
                    }
                }
            }
        }

    } else {
        ///il n'y a plus rien a parcourrir
    }


    return (_stack.size() != 0);
}
