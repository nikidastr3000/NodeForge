#include "math/trees/BinaryTree.hpp"

#include "math/graph/Graph.hpp"

namespace math::trees {

void BinaryTree::buildFromGraph(const math::graph::Graph* /*graph*/) {
    // TODO: Sequence Diagram (шаг 6): построить структуру бинарного дерева на основе переданного Graph
    // после успешной проверки графа ("checkForAVLTree").
}

void BinaryTree::addNode(int /*value*/) {
    // TODO: Добавить вершину в бинарное дерево.
    // (На Sequence Diagram шаг 10 вызывается двухпараметрический вариант addNode(id, value) у AVLTree.)
}

std::vector<math::common::Edge> BinaryTree::getEdges() const {
    // TODO: Sequence Diagram (шаг 14): вернуть список рёбер дерева в формате std::vector<Edge>
    // для передачи в Graph::rebuild при возврате в режим редактирования ("editMode") и для отрисовки.
    return {}; // TODO
}

std::vector<math::common::NodeValue> BinaryTree::getNodes() const {
    // TODO: Sequence Diagram (шаг 13): вернуть список вершин дерева (id и value) в формате std::vector<NodeValue>
    // для передачи в Graph::rebuild при возврате в режим редактирования ("editMode") и для отрисовки.
    return {}; // TODO
}

} // namespace math::trees
