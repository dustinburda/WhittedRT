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
    SolidColor,
    SimplePhong,
    Reflective,
    Refractive
};

class MaterialInterface {
public:
    explicit MaterialInterface(MaterialType mat_type);
    virtual ~MaterialInterface() = default;

    virtual Color Shade(ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights) = 0;
    MaterialType mat_type_;
};

class SolidMaterial : public MaterialInterface {
public:
    SolidMaterial(Color color) : MaterialInterface(MaterialType::SolidColor), color_{color} {

    }

    Color Shade(ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights) {
        return color_;
    }
private:
    Color color_;
};

class BlackMaterial : public MaterialInterface {
public:
    BlackMaterial();
    Color Shade(ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights) override;
};

class SimplePhongMaterial : public MaterialInterface {
public:
    SimplePhongMaterial();
    SimplePhongMaterial(Color ka, Color kd, Color ks, double p);

    Color Shade(ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights) override;

    Color ka_;
    Color kd_;
    Color ks_;
    double p_;
};


#endif //WHITTED_MATERIAL_H
