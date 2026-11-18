#pragma once

#include <vector>

struct TreeNode {
    int value = 0;
    int id = 0;
    std::vector<TreeNode*> children;
};
