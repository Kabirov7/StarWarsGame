#ifndef STARWARS_STATEPARSER_H
#define STARWARS_STATEPARSER_H

#include <iostream>
#include <vector>
#include "../xmlparsing/tinyxml.h"

class GameObject;

class StateParser
{
public:

    StateParser() {}
    ~StateParser() {}

    bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:

    void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
    void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs);
};

#endif