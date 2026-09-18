//
// Created by Dustin on 11/26/24.
//

#ifndef MESH_H
#define MESH_H


#include "OBJParser.h"
#include "ShapeInterface.h"
#include "Triangle.h"

#include <filesystem>
#include <vector>

class Mesh : public ShapeInterface {
public:
    Mesh();
    Mesh(std::shared_ptr<MeshData> mesh_data);

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override;
    bool Hit(const Ray& r, ShadeContext& context) const override;
    BoundingBox BBox() const override;
    std::vector<std::shared_ptr<ShapeInterface>> Decompose() const override;

private:
    std::vector<std::shared_ptr<Triangle>> triangles_;


    // TODO: remove, mesh no longer directly rendered
    mutable std::int64_t curr_triangle_index_;
};



#endif //MESH_H
