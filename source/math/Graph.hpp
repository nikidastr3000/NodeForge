#pragma once

#include <vector>

#include "Edge.hpp"
#include "IDrawableStructure.hpp"
#include "Node.hpp"
#include "NodeValue.hpp"

class Graph : public IDrawableStructure {
private:
    std::vector<Node> nodes;

public:
    int addNode();
    std::vector<Edge> getEdges() const override;
    std::vector<NodeValue> getNodes() const override;
    void rebuild(const std::vector<NodeValue>& nodes, const std::vector<Edge>& edges);

    // TODO: Расхождение с Sequence Diagram (шаг 5): вызывается `checkForAVLTree()` с возвратом bool (`return true`),
    // но метод отсутствует на Class Diagram. Требуется уточнить сигнатуру и добавить в диаграмму классов.

    // TODO: Расхождение с Sequence Diagram (шаг 19): вызывается `delNode(id)`,
    // но метод отсутствует на Class Diagram. Требуется уточнить сигнатуру и добавить в диаграмму классов.
};
