//
// Created by Dustin on 12/1/24.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include "OBJParser.h"
#include "ShapeInterface.h"
#include "Transformation.h"

#include <memory>

class Instance : public ShapeInterface {
public:
    Instance() = delete;
    Instance(std::shared_ptr<ShapeInterface> shape, std::shared_ptr<Material> mat);
    Instance(std::shared_ptr<Transformation> t, std::shared_ptr<ShapeInterface> shape, std::shared_ptr<Material> mat);

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override;
    bool Hit(const Ray& r, ShadeContext& context) const override;
    BoundingBox BBox() const override;


private:
    std::shared_ptr<Transformation> transform_;
    std::shared_ptr<ShapeInterface> shape_;
    std::shared_ptr<Material> mat_;
};



#endif //INSTANCE_H
