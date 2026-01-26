//
// Created by Advil on 11/20/2024.
//

#include "../include/Light.h"
#include "../include/Material.h"
#include "../include/ShadeContext.h"

MaterialInterface::MaterialInterface(MaterialType mat_type)
    : mat_type_{mat_type} {}

BlackMaterial::BlackMaterial()
    : MaterialInterface(MaterialType::Black) {}

Color BlackMaterial::Shade(ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights, double ambient_intensity) {
    return {0.0, 0.0, 0.0};
}

SimplePhongMaterial::SimplePhongMaterial()
    : MaterialInterface{MaterialType::SimplePhong} {}

SimplePhongMaterial::SimplePhongMaterial(Color ka, Color kd, Color ks)
        : MaterialInterface{MaterialType::SimplePhong}, ka_{ka}, kd_{kd}, ks_{ks} {}


Color SimplePhongMaterial::Shade(ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights, [[ maybe_unused ]] double ambient_intensity) {
    Color shade;

    shade += ka_ * ambient_intensity;

    for (auto& light : lights)
    {
        auto n_dot_l = std::max(0.0, Dot(context.normal_, light->GetDirection(context)));
        auto light_color = light->GetIntensity() * light->GetColor();
        shade += kd_ * light_color * n_dot_l;
    }

    return shade;
}
