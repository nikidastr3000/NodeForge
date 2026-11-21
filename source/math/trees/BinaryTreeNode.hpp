#pragma once

namespace math::trees {

struct BinaryTreeNode {
    int value = 0;
    int id = 0;
    BinaryTreeNode* left = nullptr;
    BinaryTreeNode* right = nullptr;
    int height = 0;
};

} // namespace math::trees
