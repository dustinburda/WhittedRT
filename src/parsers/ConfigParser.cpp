//
// Created by Dustin on 7/2/26.
//

#include "../../include/antialiasing/AdaptiveSuperSampling.h"
#include "../../include/accelerators/BVH.h"
#include "../../include/parsers/ConfigParser.h"

#include "../../include/accelerators/KDTree.h"
#include "../../include/antialiasing/SuperSampling.h"
#include "../../include/samplers/RegularSampler.h"
#include "../../include/samplers/JitteredSampler.h"
#include "../../include/samplers/RandomSampler.h"

ConfigParser::ConfigParser() : xml_parser_{XMLParser::GetInstance()} {

}


Config ConfigParser::ParseConfig(std::string config_path) {
    Config config;

    std::fstream config_file {config_path};
    std::stringstream ss;
    ss << config_file.rdbuf();

    auto config_contents = ss.str();

    auto node_ptr = xml_parser_.Parse(ss.str());

    config.num_threads_ = std::stoi(node_ptr->ChildValue("ThreadCount").value());
    config.height_ = static_cast<std::uint16_t>(std::stoi(node_ptr->ChildValue("Height").value()));
    config.width_ = static_cast<std::uint16_t>(std::stoi(node_ptr->ChildValue("Width").value()));
    config.scene_description_path_ = node_ptr->ChildValue("SceneDescriptionPath").value();
    config.output_path_ = node_ptr->ChildValue("OutputPath").value();
    config.accelerator_ = ParseAccelerator(node_ptr->ChildNode("Accelerator"));
    config.antialiasing_ = ParseAntiAliasing(node_ptr->ChildNode("AntiAliasing"));

    return config;
}

std::unique_ptr<AcceleratorInterface> ConfigParser::ParseAccelerator(const XMLNode* node) {
    auto type = node->attributes_.at("type");

    if (type == "BVH") {
        auto primitive_leaf_count = std::stoi(node->ChildValue("PrimitiveLeafCount").value());
        auto split_method = BVH::StringToSplitMethod(node->ChildValue("SplitMethod").value());

        return std::make_unique<BVH>(primitive_leaf_count, split_method);
    } else if (type == "KDTree") {
        auto primitive_leaf_count = std::stoi(node->ChildValue("PrimitiveLeafCount").value());

        return std::make_unique<KDTree>(primitive_leaf_count);
    }

    return nullptr;
}

std::unique_ptr<AntiAliasingInterface> ConfigParser::ParseAntiAliasing(const XMLNode* node) {
    auto type = node->attributes_.at("type");

    if (type == "AdaptiveSuperSampling") {
        auto sampler = std::make_unique<RegularSampler>(1);

        auto depth_count = std::stoi(node->ChildValue("Depth").value());
        auto anti_aliasing = std::make_unique<AdaptiveSuperSampling>(std::move(sampler), depth_count);

    } else if (type == "SuperSampling") {
        auto sampler = ParseSampler(node->ChildNode("Sampler"));

        auto anti_aliasing = std::make_unique<SuperSampling>(std::move(sampler));
    }

    return std::make_unique<SuperSampling>(std::make_unique<RegularSampler>(1));
}

std::unique_ptr<SamplerInterface> ConfigParser::ParseSampler(const XMLNode* node) {
    auto sampler_type = node->attributes_.at("type");
    auto num_samples = std::stoi(node->attributes_.at("sample_count"));

    std::unique_ptr<SamplerInterface> sampler = nullptr;

    if (sampler_type == "jittered") {
        sampler = std::make_unique<JitteredSampler>(num_samples);
    } else if (sampler_type == "regular") {
        sampler = std::make_unique<RegularSampler>(num_samples);
    } else if (sampler_type == "random") {
        sampler = std::make_unique<RandomSampler>(num_samples);
    }

    return sampler;
}
