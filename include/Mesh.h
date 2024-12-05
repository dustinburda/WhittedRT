//
// Created by Dustin on 11/26/24.
//

#ifndef MESH_H
#define MESH_H

#include "Triangle.h"
#include "Shape.h"

#include <filesystem>
#include <vector>

using Face = std::array<int, 3>;

class Mesh : public Shape {
public:
    Mesh() = default;
    Mesh(std::filesystem::path path);

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const;
    bool Hit(const Ray& r, ShadeContext& context) const override;

private:
    Point3d ParseVertex(std::string line);
    std::array<int, 3> ParseFace(std::string line);
    Normal<double, 3> ParseNormal(std::string line);

    std::vector<Point3d> vertices_;
    std::vector<Face> faces_;
    std::vector<Normal<double, 3>> normals_;

    std::vector<Triangle> triangles_;

    mutable std::int64_t curr_triangle_index_;
};



#endif //MESH_H
