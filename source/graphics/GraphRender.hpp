#pragma once

#include <optional>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>

#include "graphics/NodeVisual.hpp"
#include "math/common/Edge.hpp"

namespace sf {
    class RenderTarget;
}

namespace math::common {
class IDrawableStructure;
}

namespace graphics {

class GraphRender {
private:
    std::unordered_map<int, NodeVisual> visualNodes;
    const math::common::IDrawableStructure* drawableStructure = nullptr;

public:
    // TODO: Расхождение с Sequence Diagram (шаг 11): вызывается `addNodeVisual(id)` с 1 аргументом,
    // тогда как на Class Diagram объявлена только сигнатура `addNodeVisual(int, float, float)`.
    void addNodeVisual(int id, float x, float y);

    void removeNodeVisual(int id);

    std::optional<int> getNodeAt(sf::Vector2f worldPos) const;

    sf::Vector2f getNodePosition(int id) const;
    void setNodePosition(int id, float x, float y);

    void setDrawableStructure(const math::common::IDrawableStructure* structure);

    // TODO: Расхождение с Sequence Diagram (шаг 18): вызывается `getNode(x, y)` с возвратом id,
    // но метод отсутствует на Class Diagram. Требуется уточнить сигнатуру и добавить в диаграмму классов.

    void render(sf::RenderTarget& target, std::optional<int> selectedNodeId) const;

    void renderPreviewEdge(sf::RenderTarget& target, int fromNodeId, sf::Vector2f toWorldPos) const;

private:
    void renderNodes(sf::RenderTarget& target, std::optional<int> selectedNodeId) const;
    void renderNode(sf::RenderTarget& target, const graphics::NodeVisual& node, bool isSelected) const;

    void renderEdges(sf::RenderTarget& target) const;
    void renderEdge(const math::common::Edge& edge, sf::RenderTarget& target) const;

};

} // namespace graphics
