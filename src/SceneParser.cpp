//
// Created by Dustin on 11/25/24.
//

#include "../include/SceneParser.h"

std::unique_ptr<World> SceneParser::ParseScene(std::filesystem::path path) {
    std::ifstream file {path};
    auto file_size = std::filesystem::file_size(path);

    std::string src;
    src.resize(file_size);
    file.read(src.data(), file_size);

    auto node = xml_parser_.Parse(src);

    for (auto& child : node->children_) {

    }

    return std::make_unique<World>();
}

SceneParser::SceneParser() : xml_parser_{XMLParser::GetInstance()} {}