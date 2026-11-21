#include "graphics/GraphRender.hpp"

#include <SFML/Graphics.hpp>

#include "math/common/Constants.hpp"
#include "math/common/IDrawableStructure.hpp"

namespace graphics {

void GraphRender::addNodeVisual(int id, float x, float y) {
    if (visuals.size() <= id)
        visuals.resize(id + 1);
    visuals[id] = NodeVisual(x, y, DEFAULT_NODE_RADIUS);
}

void GraphRender::setDrawableStructure(const math::common::IDrawableStructure* newStructure) {
    this->drawableStructure = newStructure;
}

void GraphRender::render(sf::RenderWindow& window) {

    renderNodes(window);
    renderEdges(window);
}

void GraphRender::renderNodes(sf::RenderWindow& window) {
    for (const NodeVisual& node: visuals) {
        renderNode(node, window);
    }
}

void GraphRender::renderNode(const graphics::NodeVisual& node, sf::RenderWindow& window) {
    sf::CircleShape circle(node.radius);
    circle.setFillColor(DEFAULT_NODE_COLOR);        //TODO: change for different color for every node
    circle.setPosition(node.x, node.y);

    window.draw(circle);
}

void GraphRender::renderEdges(sf::RenderWindow &window) {
    std::vector<math::common::Edge> edges = drawableStructure->getEdges();
    for (const math::common::Edge& edge: edges) {
        renderEdge(edge, window);
    }
}

void GraphRender::renderEdge(const math::common::Edge& edge, sf::RenderWindow& window) {

}


} // namespace graphics
