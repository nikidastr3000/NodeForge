#pragma once

#include <vector>

#include "math/common/Edge.hpp"
#include "math/common/IDrawableStructure.hpp"
#include "math/common/NodeValue.hpp"
#include "math/trees/BinaryTreeNode.hpp"

namespace math::graph {
class Graph;
}

namespace math::trees {

class BinaryTree : public math::common::IDrawableStructure {
protected:
    BinaryTreeNode* root = nullptr;

public:
    void buildFromGraph(const math::graph::Graph* graph);

    // TODO: На Class Diagram у BinaryTree объявлен `+ addNode(int):` с одним параметром,
    // тогда как у наследников BinarySearchTree и AVLTree — `+ addNode(int, int):`
    // (на Sequence Diagram шаг 10: `addNode(id, value)`). Требуется уточнить согласованность сигнатур.
    void addNode(int value);

    std::vector<math::common::Edge> getEdges() const override;
    std::vector<math::common::NodeValue> getNodes() const override;
};

} // namespace math::trees
