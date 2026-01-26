//
// Created by Advil on 11/20/2024.
//

#ifndef WHITTED_MATERIAL_H
#define WHITTED_MATERIAL_H

#include "Canvas.h"
#include "Point.h"

#include <vector>
#include <memory>

class Light;
struct ShadeContext;

enum class MaterialType {
    Black,
    SimplePhong,
    Reflective,
    Refractive
};

class MaterialInterface {
public:
    explicit MaterialInterface(MaterialType mat_type);
    virtual ~MaterialInterface() = default;

    virtual Color Shade(ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights, double ambient_intensity) = 0;
    MaterialType mat_type_;
};

class BlackMaterial : public MaterialInterface {
public:
    BlackMaterial();
    Color Shade(ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights, double ambient_intensity) override;
};

class SimplePhongMaterial : public MaterialInterface {
public:
    SimplePhongMaterial();
    SimplePhongMaterial(Color ka, Color kd, Color ks);

    Color Shade(ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights, double ambient_intensity) override;

    Color ka_;
    Color kd_;
    Color ks_;
};


#endif //WHITTED_MATERIAL_H
