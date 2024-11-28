//
// Created by Dustin on 11/26/24.
//

#ifndef MESH_H
#define MESH_H

#include "Triangle.h"

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

using Face = std::array<int, 3>;

class Mesh {
public:
    Mesh() = default;
    Mesh(std::filesystem::path path);

    void GetTriangles(std::vector<Triangle>& triangles, std::shared_ptr<Material> mat = nullptr);

private:
    Point3d ParseVertex(std::string line);
    std::array<int, 3> ParseFace(std::string line);
    Normal<double, 3> ParseNormal(std::string line);

    std::vector<Point3d> vertices_;
    std::vector<Face> faces_;
    std::vector<Normal<double, 3>> normals_;
};



#endif //MESH_H
