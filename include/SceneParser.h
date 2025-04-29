//
// Created by Dustin on 11/25/24.
//

#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include "World.h"
#include "XMLParser.h"
#include "World.h"

#include <string>
#include <filesystem>

class SceneParser {
public:
    std::unique_ptr<World> ParseScene(std::filesystem::path path);

private:
    SceneParser();

    XMLParser& xml_parser_;
};



#endif //SCENEPARSER_H
