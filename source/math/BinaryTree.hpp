#pragma once

#include <vector>

#include "BinaryTreeNode.hpp"
#include "Edge.hpp"
#include "IDrawableStructure.hpp"
#include "NodeValue.hpp"

class Graph;

class BinaryTree : public IDrawableStructure {
protected:
    BinaryTreeNode* root = nullptr;

public:
    void buildFromGraph(const Graph* graph);

    // TODO: На Class Diagram у BinaryTree объявлен `+ addNode(int):` с одним параметром,
    // тогда как у наследников BinarySearchTree и AVLTree — `+ addNode(int, int):`
    // (на Sequence Diagram шаг 10: `addNode(id, value)`). Требуется уточнить согласованность сигнатур.
    void addNode(int value);

    std::vector<Edge> getEdges() const override;
    std::vector<NodeValue> getNodes() const override;
};
