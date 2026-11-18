#pragma once

#include "BinarySearchTree.hpp"

class AVLTree : public BinarySearchTree {
public:
    void addNode(int id, int value) override;
};
