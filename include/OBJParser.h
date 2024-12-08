//
// Created by Dustin on 12/7/24.
//

#ifndef OBJPARSER_H
#define OBJPARSER_H


#include "Point.h"
#include "Normal.h"

#include <filesystem>
#include <memory>
#include <vector>

using Face = std::array<int, 3>;

struct MeshData {
    std::vector<Point3d> vertices_;
    std::vector<Face> faces_;
    std::vector<Normal<double, 3>> normals_;
};

class OBJParser {
public:
    std::shared_ptr<MeshData> ParseOBJ(std::filesystem::path path);
private:
    Point3d ParseVertex(std::string line, std::shared_ptr<MeshData> mesh_data);
    std::array<int, 3> ParseFace(std::string line, std::shared_ptr<MeshData> mesh_data);
    Normal<double, 3> ParseNormal(std::string line, std::shared_ptr<MeshData> mesh_data);
};



#endif //OBJPARSER_H
