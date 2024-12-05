//
// Created by Dustin on 11/26/24.
//

#include "../include/Mesh.h"

#include <fstream>
#include <memory>
#include <string>


Mesh::Mesh(std::filesystem::path path)
    : curr_triangle_index_{-1}
{
    std::ifstream mesh_file{path};

    if (!mesh_file.is_open())
        throw std::logic_error("Please provide a valid path");

    std::string line;
    while(std::getline(mesh_file, line)) {
        if((line.substr(0, 2) == "v "))
            ParseVertex(line);
        else if(line[0] == 'f')
            ParseFace(line);
        else if(line.substr(0, 2) == "vn")
            ParseNormal(line);
    }

    for(int index = 0; auto& face : faces_) {
        auto [f1, f2, f3] = face;
        triangles_.emplace_back(vertices_[f1], vertices_[f2], vertices_[f3]);
    }
}

Point3d Mesh::ParseVertex(std::string line) {
    std::string token;
    std::stringstream s_line {line};

    Point3d p;
    for(int i = 0; i < 4; i++){
        std::getline(s_line >> std::ws, token, ' ');

        if(token == "v")
            continue;
        p[i - 1] = std::stod(token);
    }

    vertices_.push_back(p);
}

std::array<int, 3> Mesh::ParseFace(std::string line) {
    std::string token;
    std::stringstream s_line {line};

    std::vector<int> indices;
    while (std::getline(s_line >> std::ws, token, ' ')) {
        if(token == "f")
            continue;

        std::string index;
        std::stringstream s_token{token};
        std::getline(s_token, index);
        indices.push_back(std::stoi(index) - 1);
    }


    for(int i = 1; i < indices.size() - 1; i++) {
        std::array<int, 3> face = {indices[0], indices[i], indices[i + 1]};
        faces_.push_back(face);
    }
}

 Normal<double, 3> Mesh::ParseNormal(std::string line) {
    std::string token;
    std::stringstream s_line {line};

    Normal<double, 3> normal;
    for(int i = 0; i < 4; i++){
        std::getline(s_line >> std::ws, token, ' ');

        if(token == "vn")
            continue;
        normal[i - 1] = std::stod(token);
    }

    normals_.push_back(normal);
}

Normal<double, 3> Mesh::NormalAt(const Point<double, 3>& p) const {
    if (curr_triangle_index_ == -1)
        return {-1.0, -1.0, -1.0};

    auto [f1, f2, f3] = faces_[curr_triangle_index_];
    Triangle t(vertices_[f1], vertices_[f2], vertices_[f3]);
    return t.NormalAt(p);
}

bool Mesh::Hit(const Ray& r, ShadeContext& context) const {
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