//
// Created by Dustin on 12/7/24.
//

#include "../include/OBJParser.h"

#include <fstream>
#include <string>
#include <sstream>

std::shared_ptr<MeshData> OBJParser::ParseOBJ(std::filesystem::path path)
{
    std::ifstream mesh_file{path};

    if (!mesh_file.is_open())
        throw std::logic_error("Please provide a valid path");

    auto mesh_data = std::make_shared<MeshData>();

    std::string line;
    while(std::getline(mesh_file, line)) {
        if((line.substr(0, 2) == "v "))
            ParseVertex(line, mesh_data);
        else if(line[0] == 'f')
            ParseFace(line, mesh_data);
        else if(line.substr(0, 2) == "vn")
            ParseNormal(line, mesh_data);
    }

    return mesh_data;
}

Point3d OBJParser::ParseVertex(std::string line, std::shared_ptr<MeshData> mesh_data) {
    std::string token;
    std::stringstream s_line {line};

    Point3d p;
    for(int i = 0; i < 4; i++){
        std::getline(s_line >> std::ws, token, ' ');

        if(token == "v")
            continue;
        p[i - 1] = std::stod(token);
    }

    mesh_data->vertices_.push_back(p);
}

std::array<int, 3> OBJParser::ParseFace(std::string line, std::shared_ptr<MeshData> mesh_data) {
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
        mesh_data->faces_.push_back(face);
    }
}

 Normal<double, 3> OBJParser::ParseNormal(std::string line, std::shared_ptr<MeshData> mesh_data) {
    std::string token;
    std::stringstream s_line {line};

    Normal<double, 3> normal;
    for(int i = 0; i < 4; i++){
        std::getline(s_line >> std::ws, token, ' ');

        if(token == "vn")
            continue;
        normal[i - 1] = std::stod(token);
    }

    mesh_data->normals_.push_back(normal);
}