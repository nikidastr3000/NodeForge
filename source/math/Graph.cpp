#include "Graph.hpp"

int Graph::addNode() {
    // TODO: Sequence Diagram (шаги 2, 9): создать новую вершину в графе (по клику мыши в режиме редактирования
    // или перед добавлением вершины в AVLTree) и вернуть её id.
    return {}; // TODO
}

std::vector<Edge> Graph::getEdges() const {
    // TODO: Вернуть список рёбер графа в формате std::vector<Edge> для реализации IDrawableStructure.
    return {}; // TODO
}

std::vector<NodeValue> Graph::getNodes() const {
    // TODO: Вернуть список вершин графа (id и value) в формате std::vector<NodeValue> для реализации IDrawableStructure.
    return {}; // TODO
}

void Graph::rebuild(const std::vector<NodeValue>& /*nodes*/, const std::vector<Edge>& /*edges*/) {
    // TODO: Sequence Diagram (шаг 15): перестроить граф из списков вершин и рёбер,
    // полученных от дерева при переходе обратно в режим редактирования ("editMode").
}
