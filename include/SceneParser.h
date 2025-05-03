//
// Created by Dustin on 11/25/24.
//

#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include "World.h"
#include "XMLParser.h"
#include "World.h"

#include <filesystem>
#include <string>
#include <unordered_map>

class SceneParser {
public:
    static SceneParser& GetInstance() {
        static SceneParser p;

        return p;
    }

    std::unique_ptr<World> ParseScene(std::filesystem::path path);

private:
    SceneParser();

    XMLParser& xml_parser_;
};



#endif //SCENEPARSER_H
