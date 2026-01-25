#include "../include/Light.h"

Light::Light() : intensity_{1.0}, light_color_{1.0f, 1.0f, 1.0f} { }

Light::Light(double intensity, Color light_color)
    : intensity_{intensity}, light_color_{light_color} { }

double Light::GetIntensity() const {
    return intensity_;
}

Color Light::GetColor() const {
    return light_color_;
}