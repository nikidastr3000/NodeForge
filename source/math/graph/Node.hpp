#pragma once

#include <vector>

namespace math::graph {

class Node {
public:
    int id = 0;
    int value = 0;
    bool isAlive = false;
    std::vector<int> neighbours;

    Node(const int id, const int value) : id(id), value(value), isAlive(true) {}

    // TODO: На Class Diagram указана заглушка `+ method(type): type` с неопределённым именем и типами.
    // Требуется уточнить сигнатуру метода или удалить шаблонный элемент диаграммы.
};

} // namespace math::graph
