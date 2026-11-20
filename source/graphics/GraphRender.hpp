#pragma once

#include <vector>

#include "graphics/NodeVisual.hpp"

namespace math::common {
class IDrawableStructure;
}

namespace graphics {

class GraphRender {
private:
    std::vector<NodeVisual> visuals;
    const math::common::IDrawableStructure* structure = nullptr;

public:
    // TODO: Расхождение с Sequence Diagram (шаг 11): вызывается `addNodeVisual(id)` с 1 аргументом,
    // тогда как на Class Diagram объявлена только сигнатура `addNodeVisual(int, float, float)`.
    void addNodeVisual(int id, float x, float y);

    // TODO: На Class Diagram в типе параметра допущена опечатка `const IDrawableStrucrue*` (исправлено на `const IDrawableStructure*`).
    // TODO: Расхождение с Sequence Diagram (шаг 16): вызывается `setNewDrawableStructure(graph)` вместо `setDrawableStructure(...)`.
    void setDrawableStructure(const math::common::IDrawableStructure* structure);

    // TODO: Расхождение с Sequence Diagram (шаг 18): вызывается `getNode(x, y)` с возвратом id,
    // но метод отсутствует на Class Diagram. Требуется уточнить сигнатуру и добавить в диаграмму классов.
};

} // namespace graphics
