#pragma once

#include "math/trees/BinaryTree.hpp"

namespace math::trees {

class BinarySearchTree : public BinaryTree {
private:
    int direction = 0;

public:
    virtual void addNode(int id, int value);
};

} // namespace math::trees
