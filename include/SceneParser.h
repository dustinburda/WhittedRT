//
// Created by Dustin on 11/25/24.
//

#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include "World.h"
#include "XMLParser.h"

#include <string>

class SceneParser {
public:
    explicit SceneParser(std::string src) : src_{std::move(src)} {}



private:
    std::string src_;
    XMLParser* parser_;
};



#endif //SCENEPARSER_H
