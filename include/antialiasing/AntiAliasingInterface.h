//
// Created by Dustin on 11/1/26.
//

#ifndef WHITTED_ANTIALIASINGINTERFACE_H
#define WHITTED_ANTIALIASINGINTERFACE_H

#include "../../include/parsers/SceneParser.h"
#include "../samplers/SamplerInterface.h"
#include "../util/Color.h"

class AntiAliasingInterface {
public:
    AntiAliasingInterface(std::unique_ptr<SamplerInterface>& sampler);
    virtual ~AntiAliasingInterface();

    virtual Color SamplePixel(const Scene& scene, const ImagePlane& p, std::size_t x, std::size_t y) = 0;
protected:
    std::unique_ptr<SamplerInterface>& sampler_;
};

#endif //WHITTED_ANTIALIASINGINTERFACE_H
