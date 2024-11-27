//
// Created by Dustin on 11/26/24.
//

#ifndef MESH_H
#define MESH_H

#include "Triangle.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>



class Mesh {
public:
    Mesh() = delete;
    Mesh(std::filesystem::path path);

    void GetTriangles(std::vector<Triangle>& triangles);

private:
    Point3d ParseVertex(std::string line);
    std::array<int, 3> ParseFace(std::string line);
    Normal<double, 3> ParseNormal(std::string line);

    std::vector<Point3d> vertices_;
    std::vector<std::array<int, 3>> faces_;
    std::vector<Normal<double, 3>> normals_;
};



#endif //MESH_H
