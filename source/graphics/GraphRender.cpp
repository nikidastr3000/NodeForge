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

void GraphRender::setDrawableStructure(const math::common::IDrawableStructure* newStructure) {
    this->drawableStructure = newStructure;
}

void GraphRender::render(sf::RenderWindow& window) const {
    assert(drawableStructure && "drawableStructure has to be initialized");

    renderEdges(window);

    renderNodes(window);
}

void GraphRender::renderNodes(sf::RenderWindow& window) const {
    std::vector<math::common::NodeValue> nodes = drawableStructure->getNodes();
    for (const math::common::NodeValue& node: nodes) {
        assert(node.id >= 0 && "Node id cannot be negative");
        auto it = visualNodes.find(node.id);
        assert(it != visualNodes.end() && "Missing visual node for graph node");
        if (it != visualNodes.end()) {
            renderNode(it->second, window); //TODO: add a node value as parameter
        }
    }
}

void GraphRender::renderNode(const graphics::NodeVisual& node, sf::RenderWindow& window) const {
    sf::CircleShape circle(node.radius);
    circle.setOrigin(node.radius, node.radius);
    circle.setFillColor(DEFAULT_NODE_COLOR);        //TODO: change for different color for every node
    circle.setPosition(node.x, node.y);

    window.draw(circle);
}

void GraphRender::renderEdges(sf::RenderWindow &window) const {
    std::vector<math::common::Edge> edges = drawableStructure->getEdges();
    for (const math::common::Edge& edge: edges) {
        renderEdge(edge, window);
    }
}

void GraphRender::renderEdge(const math::common::Edge& edge, sf::RenderWindow& window) const {

}


} // namespace graphics
