//
// Created by Dustin on 11/26/24.
//

#include "../include/Mesh.h"

Mesh::Mesh(std::shared_ptr<MeshData> mesh_data)
    : curr_triangle_index_{-1}
{
    for(auto& face : mesh_data->faces_) {
        auto [vi1, vi2, vi3] = face;

        bool contains_texture_coordinates = mesh_data->texture_coordinates_.size() > 0;

        triangles_.emplace_back(Vertex{mesh_data->GetVertex(vi1.vertex_index_), mesh_data->GetTextureCoordinate(vi1.texture_index_) },
                                Vertex{mesh_data->GetVertex(vi2.vertex_index_), mesh_data->GetTextureCoordinate(vi2.texture_index_) },
                                Vertex{mesh_data->GetVertex(vi3.vertex_index_), mesh_data->GetTextureCoordinate(vi3.texture_index_) });
    }
}

Normal<double, 3> Mesh::NormalAt(const Point<double, 3>& p) const {
    // TODO: Remove, we don't directly render a mesh anymore
    if (curr_triangle_index_ == -1)
        return {-1.0, -1.0, -1.0};

    auto& triangle = triangles_[curr_triangle_index_];
    return triangle.NormalAt(p);

}

bool Mesh::Hit(const Ray& r, ShadeContext& context) const {
    // TODO: Remove, we don't directly render a mesh anymore
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

BoundingBox Mesh::BBox() const {
    BoundingBox b = triangles_[0].BBox();

    for ( auto& triangle : triangles_ ) {
        b = Union(b, triangle.BBox());
    }

    return b;
}

const std::vector<Triangle>& Mesh::Triangles() const {
    return triangles_;
}