//
// Created by Dustin on 7/2/26.
//

#ifndef WHITTED_CONFIGPARSER_H
#define WHITTED_CONFIGPARSER_H

#include "../accelerators/AcceleratorInterface.h"
#include "../antialiasing/AntiAliasingInterface.h"
#include "XMLParser.h"

struct Config {
    int num_threads_;

    uint16_t height_;
    uint16_t width_;


    std::string scene_description_path_;
    std::string output_path_;

    std::unique_ptr<AcceleratorInterface> accelerator_;
    std::unique_ptr<AntiAliasingInterface> antialiasing_;
};

class ConfigParser {
public:
    static ConfigParser& GetInstance() {
        static ConfigParser parser;
        return parser;
    }

    Config ParseConfig(std::string config_path);

private:
    ConfigParser();
    std::unique_ptr<AcceleratorInterface> ParseAccelerator(const XMLNode* node);
    std::unique_ptr<AntiAliasingInterface> ParseAntiAliasing(const XMLNode* node);
    std::unique_ptr<SamplerInterface> ParseSampler(const XMLNode* node);

private:
    XMLParser& xml_parser_;
};


#endif //WHITTED_CONFIGPARSER_H
