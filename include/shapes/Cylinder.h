//
// Created by Dustin on 8/13/25.
//

#ifndef WHITTED_CYLINDER_H
#define WHITTED_CYLINDER_H

#include "Disk.h"
#include "ShapeInterface.h"

class UncappedCylinder : public ShapeInterface {
public:
    UncappedCylinder();
    virtual ~UncappedCylinder() override;

    std::optional<Normal<double, 3>> NormalAt(const Point<double, 3>& p) const override;
    bool Hit(const Ray& r, ShadeContext& context) const override;
    BoundingBox BBox() const override;
    std::vector<std::shared_ptr<ShapeInterface>> Decompose() const override;
};

class Cylinder : public ShapeInterface {
public:
    Cylinder();
    ~Cylinder() override;

    std::optional<Normal<double, 3>> NormalAt(const Point<double, 3>& p) const  override;
    bool Hit(const Ray& r, ShadeContext& context) const  override;
    BoundingBox BBox() const  override;

    std::vector<std::shared_ptr<ShapeInterface>> Decompose() const override;

private:
    std::shared_ptr<UncappedCylinder> cylinder_;
    std::shared_ptr<Disk> cap1_;
    std::shared_ptr<Disk> cap2_;
};

#endif //WHITTED_CYLINDER_H
