#pragma once

#include "BinaryTree.hpp"

class BinarySearchTree : public BinaryTree {
private:
    int direction = 0;

public:
    virtual void addNode(int id, int value);
};
