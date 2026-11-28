#include "graphics/GraphRender.hpp"

#include <cassert>
#include <vector>

#include <SFML/Graphics.hpp>

#include "graphics/Constants.hpp"
#include "math/common/IDrawableStructure.hpp"

namespace graphics {

void GraphRender::addNodeVisual(int id, float x, float y) {
    assert(id >= 0 && "Node id cannot be negative");

    visualNodes[id] = NodeVisual(x, y, DEFAULT_NODE_RADIUS);
}

void GraphRender::removeNodeVisual(int id) {
    assert(id >= 0 && "Node id cannot be negative");

    auto iterator = visualNodes.find(id);
    assert(iterator != visualNodes.end() && "Missing visual node for this id");

    visualNodes.erase(id);
}

std::optional<int> GraphRender::getNodeAt(sf::Vector2f worldPos) const {
    assert(drawableStructure && "drawableStructure has to be initialized");
    const std::vector<math::common::NodeValue> nodes = drawableStructure->getNodes();

    // Идём с конца вектора (обратный порядок отрисовки):
    // если две вершины перекрываются, сначала проверяется верхняя.
    for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
        auto visualIt = visualNodes.find(it->id);
        assert(visualIt != visualNodes.end() && "Missing visual node for this id");

        const NodeVisual& visualNode = visualIt->second;
        const float dx = worldPos.x - visualNode.x;
        const float dy = worldPos.y - visualNode.y;

        if (dx * dx + dy * dy <= visualNode.radius * visualNode.radius) {
            return it->id;
        }

    }

    return std::nullopt;
}

sf::Vector2f GraphRender::getNodePosition(int id) const {
    auto iterator = visualNodes.find(id);
    assert(iterator != visualNodes.end() && "Missing visual node for this id");

    return {iterator->second.x, iterator->second.y};
}

void GraphRender::setNodePosition(int id, float x, float y) {
    auto iterator = visualNodes.find(id);
    assert(iterator != visualNodes.end() && "Missing visual node for this id");

    iterator->second.x = x;
    iterator->second.y = y;
}

void GraphRender::setDrawableStructure(const math::common::IDrawableStructure* newStructure) {
    this->drawableStructure = newStructure;
}

void GraphRender::render(sf::RenderTarget& target, std::optional<int> selectedNodeId) const {
    assert(drawableStructure && "drawableStructure has to be initialized");

    renderEdges(target);

    renderNodes(target, selectedNodeId);
}

void GraphRender::renderPreviewEdge(sf::RenderTarget& target, int fromNodeId, sf::Vector2f toWorldPos) const {
    const sf::Vector2f fromPos = getNodePosition(fromNodeId);

    sf::Vertex line[] = {
        sf::Vertex(fromPos, DEFAULT_PREVIEW_EDGE_COLOR),
        sf::Vertex(toWorldPos, DEFAULT_PREVIEW_EDGE_COLOR)
    };

    target.draw(line, 2, sf::Lines);
}

void GraphRender::renderNodes(sf::RenderTarget& target, std::optional<int> selectedNodeId) const {
    std::vector<math::common::NodeValue> nodes = drawableStructure->getNodes();
    for (const math::common::NodeValue& node: nodes) {
        assert(node.id >= 0 && "Node id cannot be negative");

        auto iterator = visualNodes.find(node.id);
        assert(iterator != visualNodes.end() && "Missing visual node for this id");

        const bool isSelected = (node.id == selectedNodeId);

        renderNode(target, iterator->second, isSelected); //TODO: add a node value as parameter
    }
}

void GraphRender::renderNode(sf::RenderTarget& target, const graphics::NodeVisual& node, bool isSelected) const {
    sf::CircleShape circle(node.radius);
    circle.setOrigin(node.radius, node.radius);
    circle.setFillColor(DEFAULT_NODE_COLOR);        //TODO: change for different color for every node
    circle.setPosition(node.x, node.y);

    if (isSelected) {
        circle.setOutlineThickness(3.f);
        circle.setOutlineColor(sf::Color(255, 165, 0));
    } else {
        circle.setOutlineThickness(1.5f);
        circle.setOutlineColor(sf::Color(30, 40, 60));
    }

    target.draw(circle);
}

void GraphRender::renderEdges(sf::RenderTarget& target) const {
    std::vector<math::common::Edge> edges = drawableStructure->getEdges();
    for (const math::common::Edge& edge: edges) {
        renderEdge(edge, target);
    }
}

void GraphRender::renderEdge(const math::common::Edge& edge, sf::RenderTarget& target) const {
    const NodeVisual& fromNode = visualNodes.at(edge.fromId);
    const NodeVisual& toNode = visualNodes.at(edge.toId);

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(fromNode.x, fromNode.y), DEFAULT_EDGE_COLOR),
        sf::Vertex(sf::Vector2f(toNode.x, toNode.y), DEFAULT_EDGE_COLOR)
    };

    target.draw(line, 2, sf::Lines);
}


} // namespace graphics
