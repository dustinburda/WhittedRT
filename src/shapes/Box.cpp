//
// Created by Dustin on 1/26/26.
//

#include "../../include/shapes/Box.h"
#include "../../include/util/Interval.h"

Box::Box() : ShapeInterface(ShapeType::Box) {

}

std::optional<Normal<double, 3>> Box::NormalAt( const Point<double, 3>& p) const {
    if (std::abs(p[0]) > 1 + epsilon ||
        std::abs(p[1]) > 1 + epsilon ||
        std::abs(p[2]) > 1 + epsilon)
        return std::nullopt;

    auto x_one = std::abs(std::abs(p[0]) - 1) < epsilon;
    auto y_one = std::abs(std::abs(p[1]) - 1) < epsilon;
    auto z_one = std::abs(std::abs(p[2]) - 1) < epsilon;


    if (x_one + y_one + z_one == 3) // Corner
        return Normal<double, 3> {2.0 * (p[0] > 0) - 1, 0, 0};

    if (x_one + y_one + z_one == 2) {
        if (x_one + y_one == 2)
            return Normal<double, 3> {2.0 * (p[0] > 0) - 1, 0, 0};
        if (y_one + z_one == 2)
            return Normal<double, 3> {0, 2.0 * (p[1] > 0) - 1, 0};
        if (z_one + x_one == 2)
            return Normal<double, 3> {0, 0, 2.0 * (p[2] > 0) - 1};
    }

    if (x_one)
        return Normal<double, 3> {2.0 * (p[0] > 0) - 1, 0, 0};

    if (y_one)
        return Normal<double, 3> {0, 2.0 * (p[1] > 0) - 1, 0};

    if (z_one)
        return Normal<double, 3> {0, 0, 2.0 * (p[2] > 0) - 1};

    return std::nullopt;
}

bool Box::Hit(const Ray& r, ShadeContext& context) const {
    Point3D orig = r.Origin();
    Vec3D dir = r.Direction();

    // TODO: handle when ray direction is parallel to slabs
    Interval x_interval {(-1 - orig[0])/dir[0], (1 - orig[0])/dir[0] };
    Interval y_interval {(-1 - orig[1])/dir[1], (1 - orig[1])/dir[1] };
    Interval z_interval {(-1 - orig[2])/dir[2], (1 - orig[2])/dir[2] };

    if (!Interval::Intersects({x_interval, y_interval, z_interval}))
        return false;

    double hit_time;

    auto enter = std::max({ x_interval.t_min_, y_interval.t_min_, z_interval.t_min_});
    auto exit = std::min({ x_interval.t_max_, y_interval.t_max_, z_interval.t_max_});
    if (enter > context.t_min_ && enter < context.t_max_)
        hit_time = enter;
    else if (exit > context.t_min_ && exit < context.t_max_)
        hit_time = exit;
    else
        return false;

    auto hit_point = r.At(hit_time);

    context.t_max_= hit_time;
    context.point_ = hit_point;
    context.normal_ = NormalAt(hit_point).value();

    return true;
}

BoundingBox Box::BBox() const {
    return BoundingBox{Point3D {-1, -1, -1}, Point3D {1, 1, 1}};
}

std::vector<std::shared_ptr<ShapeInterface>> Box::Decompose() const {
    return {};
}