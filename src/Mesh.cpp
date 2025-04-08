//
// Created by Dustin on 11/26/24.
//

#include "../include/Mesh.h"

Mesh::Mesh(std::shared_ptr<MeshData> mesh_data)
    : curr_triangle_index_{-1}
{
    for(auto& face : mesh_data->faces_) {
        auto [vi1, vi2, vi3] = face;

        bool is_textured_triangle = mesh_data->GetTextureCoordinate(vi1) != std::nullopt;

        triangles_.emplace_back(Vertex{mesh_data->GetVertex(vi1), mesh_data->GetTextureCoordinate(vi1) },
                                Vertex{mesh_data->GetVertex(vi2), mesh_data->GetTextureCoordinate(vi2) },
                                Vertex{mesh_data->GetVertex(vi3), mesh_data->GetTextureCoordinate(vi3) });
        triangles_.back().SetIsTextured(is_textured_triangle);
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