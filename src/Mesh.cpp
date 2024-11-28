//
// Created by Dustin on 11/26/24.
//

#include "../include/Mesh.h"


Mesh::Mesh(std::filesystem::path path)
{
    std::ifstream mesh_file{path};

    if (!mesh_file.is_open())
        throw std::logic_error("Please provide a valid path");

    std::string line;
    while(std::getline(mesh_file, line)) {
        if(line[0] == 'v')
            vertices_.push_back(ParseVertex(line));
        else if(line[0] == 'f')
            faces_.push_back(ParseFace(line));
        else if(line.substr(0, 2) == "vn")
            normals_.push_back(ParseNormal(line));
    }
}

void Mesh::GetTriangles(std::vector<Triangle>& triangles, std::shared_ptr<Material> mat)
{
    for(auto& face : faces_) {
        auto [f1, f2, f3] = face;
        triangles.emplace_back(vertices_[f1 - 1], vertices_[f2 - 1], vertices_[f3 - 1], mat);
    }
}

Point3d Mesh::ParseVertex(std::string line) {
    std::string token;
    std::stringstream s_line {line};

    Point3d p;
    for(int i = 0; i < 4; i++){
        std::getline(s_line, token, ' ');

        if(token == "v")
            continue;
        p[i - 1] = std::stod(token);
    }

    return p;
}

std::array<int, 3> Mesh::ParseFace(std::string line) {
    std::string token;
    std::stringstream s_line {line};

    std::array<int, 3> face;
    for(int i = 0; i < 4; i++){
        std::getline(s_line, token, ' ');

        if(token == "f")
            continue;

        std::string index;
        std::stringstream s_token{token};
        std::getline(s_token, index);
        face[i - 1] = std::stoi(index) - 1;
    }

    return face;
}

 Normal<double, 3> Mesh::ParseNormal(std::string line) {
    std::string token;
    std::stringstream s_line {line};

    Normal<double, 3> normal;
    for(int i = 0; i < 4; i++){
        std::getline(s_line, token, ' ');

        if(token == "vn")
            continue;
        normal[i - 1] = std::stod(token);
    }

    return normal;
}