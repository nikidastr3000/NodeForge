#pragma once

#include <vector>

class Node {
public:
    int id = 0;
    int value = 0;
    bool isAlive = false;
    std::vector<int> neighbours;

    // TODO: На Class Diagram указана заглушка `+ method(type): type` с неопределённым именем и типами.
    // Требуется уточнить сигнатуру метода или удалить шаблонный элемент диаграммы.
};
