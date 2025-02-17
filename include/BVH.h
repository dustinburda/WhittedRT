//
// Created by Dustin on 12/22/24.
//

#ifndef BVH_H
#define BVH_H

#include "BoundingBox.h"
#include "Instance.h"

#include <memory>
#include <optional>

struct BVHNode {
public:
    BVHNode();

private:
    std::unique_ptr<BVHNode> left_;
    std::unique_ptr<BVHNode> right_;
    BoundingBox bounding_box_;

    std::optional<Instance> instance_;
    bool is_leaf_;

};

class BVH {
public:
    BVH(std::vector<Instance>& shapes) {
        root_ = Build(shapes);
    }


private:
    std::unique_ptr<BVHNode> Build(std::vector<Instance>& shapes) {
        if (shapes.size() == 1) {
            return nullptr;
        }

        return nullptr;
    }

    std::unique_ptr<BVHNode> root_;
};



#endif //BVH_H


