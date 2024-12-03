//
// Created by Dustin on 11/26/24.
//

#ifndef MESH_H
#define MESH_H

#include "Triangle.h"
#include "Shape.h"

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

using Face = std::array<int, 3>;

class Mesh : public Shape {
public:
    Mesh() = default;
    Mesh(std::filesystem::path path);

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const {
        if (curr_triangle_index_ == -1)
            return {-1.0, -1.0, -1.0};

        auto [f1, f2, f3] = faces_[curr_triangle_index_];
        Triangle t(vertices_[f1], vertices_[f2], vertices_[f3]);
        return t.NormalAt(p);
    }


    bool Hit(const Ray& r, ShadeContext& context) const override {
        bool hit = false;

        for(int index = 0; const auto& triangle : triangles_) {
            if(triangle.Hit(r, context)) {
                hit = true;
                curr_triangle_index_ = index;
            }
            index++;
        }

        return hit;
    }

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
