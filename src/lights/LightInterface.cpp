#include "../../include/lights/LightInterface.h"

LightInterface::LightInterface() : intensity_{1.0}, light_color_{1.0f, 1.0f, 1.0f} { }

LightInterface::LightInterface(double intensity, Color light_color)
    : intensity_{intensity}, light_color_{light_color} { }

double LightInterface::GetIntensity() const {
    return intensity_;
}

Color LightInterface::GetColor() const {
    return light_color_;
}