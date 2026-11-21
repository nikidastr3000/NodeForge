#include "math/graph/Graph.hpp"

#include <cassert>

namespace math::graph {

int Graph::addNode() {
    for (Node& node: nodes) {
        if (node.isAlive == false) {
            node.isAlive = true;
            node.value = node.id;
            node.neighbours.clear();
            return node.id;
        }
    }

    int newId = nextId++;
    nodes.emplace_back(newId, newId);
    return newId;
}

void Graph::addEdge(int fromId, int toId) {
    assert(fromId >= 0 && "fromId cannot be negative");
    assert(toId >= 0 && "toId cannot be negative");

    assert(fromId < nodes.size() && "fromId has to be in the range");
    assert(toId < nodes.size() && "toId has to be in the range");

    assert(nodes[fromId].isAlive && "the node(fromId) has to be alive");
    assert(nodes[toId].isAlive && "the node(toId) has to be alive");

    nodes[fromId].neighbours.emplace_back(toId);
    nodes[toId].neighbours.emplace_back(fromId);    //delete this line, if the graph is directed
}


std::vector<math::common::Edge> Graph::getEdges() const {
    std::vector<math::common::Edge> edges;
    for (int i = 0; i < nodes.size(); ++i) {
        for (int neighbourId: nodes[i].neighbours) {
            if (neighbourId > i) {   //to avoid duplicates // delete if the graph is directed
                edges.emplace_back(i, neighbourId);
            }
        }
    }

    return edges;
}

std::vector<math::common::NodeValue> Graph::getNodes() const {
    std::vector<math::common::NodeValue> valueNodes = {};
    valueNodes.reserve(nodes.size());

    for (const Node& graphNode: this->nodes) {
        if (graphNode.isAlive) {
            valueNodes.emplace_back(graphNode.id, graphNode.value);
        }
    }

    return valueNodes;
}

void Graph::rebuild(const std::vector<math::common::NodeValue>& /*nodes*/,
                    const std::vector<math::common::Edge>& /*edges*/) {
    // TODO: Sequence Diagram (шаг 15): перестроить граф из списков вершин и рёбер,
    // полученных от дерева при переходе обратно в режим редактирования ("editMode").
}

} // namespace math::graph
