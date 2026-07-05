//
// Created by Dustin on 7/2/26.
//

#ifndef WHITTED_CONFIGPARSER_H
#define WHITTED_CONFIGPARSER_H

#include "XMLParser.h"

enum class CameraType {
    Projective,
    Orthographic
};

struct Config {
    int num_threads_;

    uint16_t height_;
    uint16_t width_;


    std::string scene_description_path_;
    std::string output_path_;

    CameraType camera_type_;
};

class ConfigParser {
public:
    static ConfigParser GetInstance() {
        static ConfigParser parser;
        return parser;
    }

    Config ParseConfig(std::string config_path) {
        Config config;

        auto node_ptr = xml_parser_.Parse(config_path);

        config.height_ = std::stoi(node_ptr->ChildValue("Height").value());
        config.width_ = std::stoi(node_ptr->ChildValue("Width").value());
        config.scene_description_path_ = node_ptr->ChildValue("scene_description_path").value();
        config.output_path_ = node_ptr->ChildValue("output_path_").value();

    }

private:
    ConfigParser();

    XMLParser& xml_parser_;
};


#endif //WHITTED_CONFIGPARSER_H
