#pragma once

#include "math/trees/BinarySearchTree.hpp"

namespace math::trees {

class AVLTree : public BinarySearchTree {
public:
    void addNode(int id, int value) override;
};

} // namespace math::trees
