#pragma once

#include <vector>

#include "math/common/Edge.hpp"
#include "math/common/IDrawableStructure.hpp"
#include "math/common/NodeValue.hpp"
#include "math/trees/TreeNode.hpp"

namespace math::trees {

class Tree : public math::common::IDrawableStructure {
private:
    TreeNode* root = nullptr;

public:
    // TODO: На Class Diagram указана заглушка `+ method(type): type` с неопределённым именем и типами.
    // Требуется уточнить сигнатуру метода или удалить шаблонный элемент диаграммы.

    std::vector<math::common::Edge> getEdges() const override;
    std::vector<math::common::NodeValue> getNodes() const override;
};

} // namespace math::trees
