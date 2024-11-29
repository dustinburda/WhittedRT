//
// Created by Advil on 11/20/2024.
//

#include "../include/World.h"


#include "../include/Material.h"
#include "../include/Mesh.h"
#include "../include/Material.h"

void World::AddShape(std::shared_ptr<Shape> shape)
{
    world_.push_back(std::move(shape));
}

bool World::Hit(const Ray& r, ShadeContext& context)
{
    bool bHit = false;

    for(const std::shared_ptr<Shape>& shape_ptr : world_)
    {
        bHit |= shape_ptr->Hit(r, context);
    }

    return bHit;
}


void World::AddMesh(std::string name, std::shared_ptr<Material> mat) {
    Mesh m(std::filesystem::current_path().parent_path().string() + "/models/" + name + ".obj");
    std::vector<Triangle> mesh;
    m.GetTriangles(mesh, mat);

    double scale_factor = 1/7.0;
    Vector<double, 3> translate {0.0, -0.5, 2.0};
    for(auto& triangle : mesh)
    {
        auto m = triangle.GetMaterial();
        auto points = triangle.Points();

        std::shared_ptr<Triangle> t = std::make_shared<Triangle>(points[0] / scale_factor  + translate, points[1] / scale_factor  + translate, points[2] / scale_factor + translate, m);
        AddShape(t);
    }
}