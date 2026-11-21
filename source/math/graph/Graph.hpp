#pragma once

#include <vector>

#include "math/common/Edge.hpp"
#include "math/common/IDrawableStructure.hpp"
#include "math/common/NodeValue.hpp"
#include "math/graph/Node.hpp"

namespace math::graph {

class Graph : public math::common::IDrawableStructure {
private:
    std::vector<Node> nodes = {};
    int nextId = 0;

public:
    int addNode();
    void addEdge(int fromId, int toId);

    std::vector<math::common::Edge> getEdges() const override;
    std::vector<math::common::NodeValue> getNodes() const override;
    void rebuild(const std::vector<math::common::NodeValue>& nodes, const std::vector<math::common::Edge>& edges);

    // TODO: Расхождение с Sequence Diagram (шаг 5): вызывается `checkForAVLTree()` с возвратом bool (`return true`),
    // но метод отсутствует на Class Diagram. Требуется уточнить сигнатуру и добавить в диаграмму классов.

    // TODO: Расхождение с Sequence Diagram (шаг 19): вызывается `delNode(id)`,
    // но метод отсутствует на Class Diagram. Требуется уточнить сигнатуру и добавить в диаграмму классов.

    Graph() = default;
};

} // namespace math::graph
