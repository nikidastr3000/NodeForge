#include "math/graph/Graph.hpp"

namespace math::graph {

int Graph::addNode() {
    for (Node& node: nodes) {
        if (node.isAlive == false) {
            node.isAlive = true;
            return node.id;
        }
    }

    int newId = nextId++;
    nodes.emplace_back(newId, 0);
    return newId++;
}

std::vector<math::common::Edge> Graph::getEdges() const {
    // TODO: Вернуть список рёбер графа в формате std::vector<Edge> для реализации IDrawableStructure.
    return {}; // TODO
}

std::vector<math::common::NodeValue> Graph::getNodes() const {
    // TODO: Вернуть список вершин графа (id и value) в формате std::vector<NodeValue> для реализации IDrawableStructure.
    return {}; // TODO
}

void Graph::rebuild(const std::vector<math::common::NodeValue>& /*nodes*/,
                    const std::vector<math::common::Edge>& /*edges*/) {
    // TODO: Sequence Diagram (шаг 15): перестроить граф из списков вершин и рёбер,
    // полученных от дерева при переходе обратно в режим редактирования ("editMode").
}

} // namespace math::graph
