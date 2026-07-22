//
// Created by Dustin on 7/2/26.
//

#ifndef WHITTED_CONFIGPARSER_H
#define WHITTED_CONFIGPARSER_H

#include "XMLParser.h"

struct Config {
    int num_threads_;

    uint16_t height_;
    uint16_t width_;


    std::string scene_description_path_;
    std::string output_path_;
};

class ConfigParser {
public:
    static ConfigParser& GetInstance() {
        static ConfigParser parser;
        return parser;
    }

    Config ParseConfig(std::string config_path) {
        Config config;

        std::fstream config_file {config_path};
        std::stringstream ss;
        ss << config_file.rdbuf();

        auto config_contents = ss.str();

        auto node_ptr = xml_parser_.Parse(ss.str());

        config.num_threads_ = std::stoi(node_ptr->ChildValue("ThreadCount").value());
        config.height_ = std::stoi(node_ptr->ChildValue("Height").value());
        config.width_ = std::stoi(node_ptr->ChildValue("Width").value());
        config.scene_description_path_ = node_ptr->ChildValue("SceneDescriptionPath").value();
        config.output_path_ = node_ptr->ChildValue("OutputPath").value();

        return config;
    }

private:
    ConfigParser();

    XMLParser& xml_parser_;
};


#endif //WHITTED_CONFIGPARSER_H
