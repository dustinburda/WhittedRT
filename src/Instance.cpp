//
// Created by Dustin on 12/1/24.
//

#include "../include/Instance.h"

Instance::Instance(std::shared_ptr<ShapeInterface> shape, std::shared_ptr<Material> mat)
    : transform_{std::make_shared<Transformation>(Transformation::Identity())}, shape_{std::move(shape)}, mat_{std::move(mat)} {}

Instance::Instance(std::shared_ptr<Transformation> t, std::shared_ptr<ShapeInterface> shape, std::shared_ptr<Material> mat)
    :transform_{t}, shape_{std::move(shape)}, mat_{std::move(mat)} {}

Normal<double, 3> Instance::NormalAt(const Point<double, 3>& p) const {
    return (*transform_)(shape_->NormalAt(p));
};

bool Instance::Hit(const Ray& r, ShadeContext& context) const {
    Ray transformed_ray = transform_->ApplyInverse(r);

    if(!shape_->Hit(transformed_ray, context))
        return false;

    context.normal_ = NormalAt(context.point_);
    context.point_ = (*transform_)(context.point_);
    context.mat_ = mat_;

    return true;
}

BoundingBox Instance::BBox() const {
    if(transform_ == nullptr)
        return shape_->BBox();

    Point3d bbox_min = shape_->BBox().Min();
    Point3d bbox_max = shape_->BBox().Max();

    auto length_x = bbox_max[0] - bbox_min[0];
    auto length_y = bbox_max[1] - bbox_min[1];
    auto length_z = bbox_max[2] - bbox_min[2];

    Point3d transformed_bbox_min = { std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max() };
    Point3d transformed_bbox_max = { std::numeric_limits<double>::min(), std::numeric_limits<double>::min(), std::numeric_limits<double>::min() };
    for (int i = 0; i < 8; i++) {
        Point3d p { bbox_min[0] + (i & (1 << 0)) * length_x,
                    bbox_min[1] + (i & (1 << 1)) * length_y,
                    bbox_min[2] + (i & (1 << 2)) * length_z };

        Point3d transformed_p = (*transform_)(p);

        for(int j = 0; j < 3; j++) {
            transformed_bbox_min[j] = std::min(transformed_bbox_min[j], transformed_p[j]);
            transformed_bbox_max[j] = std::max(transformed_bbox_max[j], transformed_p[j]);
        }
    }

    return BoundingBox {bbox_min, bbox_max};
}