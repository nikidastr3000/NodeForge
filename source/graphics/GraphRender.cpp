#include "graphics/GraphRender.hpp"

#include <SFML/Graphics.hpp>

#include "math/common/IDrawableStructure.hpp"

namespace graphics {

void GraphRender::addNodeVisual(int /*id*/, float /*x*/, float /*y*/) {
    // TODO: Sequence Diagram (шаги 3, 11): создать и сохранить визуальное представление NodeVisual
    // для вершины с указанным id и координатами (x, y) (на шаге 11 координаты не передаются — см. TODO в GraphRender.hpp).
}

void GraphRender::setDrawableStructure(const math::common::IDrawableStructure* /*structure*/) {
    // TODO: Sequence Diagram (шаги 7, 16): переключить текущую отображаемую структуру (avlTree или graph),
    // сохранив указатель structure для последующей отрисовки через SFML 2.5.
}

} // namespace graphics
