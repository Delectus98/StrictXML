//
// Created by Maxime on 16/05/2018.
//

#ifndef KEYBOARDKNOCKOUT_XMLPARSER_H
#define KEYBOARDKNOCKOUT_XMLPARSER_H

#include <stack>
#include "Xml.h"

class XmlParser final{
private:
    std::stack<std::pair<size_t, const Xml*>> _stack;
public:
    explicit XmlParser(const Xml* xml);

    ~XmlParser() = default;

    /**
     * When a XmlParser is not well formed return false
     * A XmlParser is not well formed if there is no xml to process
     * @return return false [if there is no xml >> error] or true [otherwise]
     */
    operator bool();

    /**
     * The current size of the stack is the distance between the master root and the current node + 1
     * @return the current size of the stack
     */
    size_t length() const;

    const Xml *current() const;

    /**
     * Place the current Xml to the left brother xml node (at left)
     * If there is no previous, the current Xml do not change
     * @return false if [there is no previous brother node (at left)] or [error when the parser has no xml].
     */
    bool previous();

    /**
     * Place the current Xml to the right brother xml node (at right)
     * If there is no next, the current Xml do not change
     * @return false if [there is no next brother node (at right)] or [error when the parser has no xml].
     */
    bool next();

    /**
     * Return the possible forward path of current node
     * @return The current Xml's xmls
     */
    size_t paths();

    /**
     * Place the current Xml node to the nth path of the current xml node (at right)
     * @param path The chosen path to move forward to
     * @return false if [there is no forward path] or [error when the parser has no xml].
     */
    bool forward(int path = 0);

    /**
     * Place the current Xml node to the local root
     * @return false if [there is no backward path} or [error when the parser has no xml]
     */
    bool backward();

    /**
     * Parse every xml node in the tree from current xml node until the last one.
     * Place the current Xml node to the next node that have not been reached in order
     * When return false [the current xml is the master root] or [error when the parser has no xml]
     * @return false if the last node have been reached
     */
    bool forwardAll();

    /**
     * Parse every xml node in the tree from current xml node until the first one.
     * Place the current Xml node to the previous node that have not been reached in order
     * When return false [the current xml is the master root] or [error when the parser has no xml]
     * @return false if the root node have been reached
     */
    bool backwardAll();

};

#endif //KEYBOARDKNOCKOUT_XMLPARSER_H
