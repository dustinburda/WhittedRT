//
// Created by Dustin on 11/4/26.
//

#include "../../include/accelerators/KDTree.h"

KDTree::KDTree(int num_primitives_leaf) : num_primitives_leaf{num_primitives_leaf} {

}

bool KDTree::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& s) {
    return false;
}

void KDTree::Build( [[ maybe_unused ]] std::span<InstancePtr> instances) {

}

