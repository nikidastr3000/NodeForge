#pragma once

#include <vector>

#include "Edge.hpp"
#include "IDrawableStructure.hpp"
#include "NodeValue.hpp"
#include "TreeNode.hpp"

class Tree : public IDrawableStructure {
private:
    TreeNode* root = nullptr;

public:
    // TODO: На Class Diagram указана заглушка `+ method(type): type` с неопределённым именем и типами.
    // Требуется уточнить сигнатуру метода или удалить шаблонный элемент диаграммы.

    std::vector<Edge> getEdges() const override;
    std::vector<NodeValue> getNodes() const override;
};
