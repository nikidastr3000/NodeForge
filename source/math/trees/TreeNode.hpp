#pragma once

#include <vector>

namespace math::trees {

struct TreeNode {
    int value = 0;
    int id = 0;
    std::vector<TreeNode*> children;
};

} // namespace math::trees
