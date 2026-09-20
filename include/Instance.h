//
// Created by Dustin on 12/1/24.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include "OBJParser.h"
#include "ShapeInterface.h"
#include "Transformation.h"

#include <memory>


class Instance  {
public:
    Instance() = delete;
    Instance(std::shared_ptr<ShapeInterface> shape, std::shared_ptr<MaterialInterface> mat);
    Instance(std::shared_ptr<Transformation> t, std::shared_ptr<ShapeInterface> shape, std::shared_ptr<MaterialInterface> mat);

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const;
    bool Hit(const Ray& r, ShadeContext& context) const;
    BoundingBox BBox() const;
    std::vector<Instance> Decompose() const;;

    ShapeType Type() const;
    
private:
    BoundingBox ComputeBBox();

    std::shared_ptr<Transformation> transform_;
    std::shared_ptr<ShapeInterface> shape_;
    std::shared_ptr<MaterialInterface> mat_;
    BoundingBox bounding_box_;
};



#endif //INSTANCE_H
