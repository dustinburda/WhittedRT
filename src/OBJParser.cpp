//
// Created by Dustin on 12/7/24.
//

#include "../include/OBJParser.h"

#include <fstream>
#include <string>
#include <sstream>


std::optional<Point2d> MeshData::GetTextureCoordinate(VertexIndex vi) {
    if (vi.texture_index_ == std::nullopt)
        return std::nullopt;

    return texture_coordinates_[vi.texture_index_.value()];
}

Point3d MeshData::GetVertex(VertexIndex vi) {
    return vertices_[vi.vertex_index_];
}

OBJParser& OBJParser::GetInstance() {
    static OBJParser parser;
    return parser;
}

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
        else if (line.substr(0, 2) == "vt")
            ParseTexture(line, mesh_data);
    }

    return mesh_data;
}

void OBJParser::ParseVertex(std::string line, std::shared_ptr<MeshData> mesh_data) {
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

void OBJParser::ParseFace(std::string line, std::shared_ptr<MeshData> mesh_data) {
    std::string token;
    std::stringstream s_line {line};

    std::vector<VertexIndex> indices;
    while (std::getline(s_line >> std::ws, token, ' ')) {
        if(token == "f")
            continue;

        std::string vertex_index;
        std::string texture_index;

        std::stringstream s_token{token};
        std::getline(s_token, vertex_index, '/');
        std::getline(s_token, texture_index, '/');

        VertexIndex vi = (!texture_index.empty()) ? VertexIndex{std::stoi(vertex_index) - 1, std::stoi(texture_index) - 1}
                                                  : VertexIndex{std::stoi(vertex_index) - 1};

        indices.push_back(vi);
    }

    // Face can be a quad, break it into multiple triangles
    for(int i = 1; i < indices.size() - 1; i++) {
        std::array<VertexIndex, 3> face = {indices[0], indices[i], indices[i + 1]};
        mesh_data->faces_.push_back(face);
    }
}

void OBJParser::ParseNormal(std::string line, std::shared_ptr<MeshData> mesh_data) {
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

void OBJParser::ParseTexture(std::string line, std::shared_ptr<MeshData> mesh_data) {
    std::string token;
    std::stringstream s_line {line};

    Point2d uv;
    for(int i = 0; i < 3; i++) {
        std::getline(s_line >> std::ws, token, ' ');
        if(token == "vt")
            continue;


        uv[i-1] = std::stod(token);
    }

    mesh_data->texture_coordinates_.push_back(uv);
}