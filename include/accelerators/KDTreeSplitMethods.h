//
// Created by Dustin on 11/22/26.
//

#ifndef WHITTED_KDTREESPLITMETHODS_H
#define WHITTED_KDTREESPLITMETHODS_H

#include "KDTree.h"

using ShapeSplit = std::pair<std::vector<InstancePtr>, std::vector<InstancePtr>>;


ShapeSplit Split(std::vector<InstancePtr> instances);

#endif //WHITTED_KDTREESPLITMETHODS_H
