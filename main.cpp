#include <iostream>
#include <SFML/Graphics.hpp>

#include "source/graphics/GraphRender.hpp"
#include "math/graph/Graph.hpp"

using namespace std;

int main() {
    math::graph::Graph graph = math::graph::Graph();
    graphics::GraphRender graphRender = graphics::GraphRender();
    graphRender.setDrawableStructure(&graph);

    int id;
    id = graph.addNode();
    graphRender.addNodeVisual(id, 0, 0);

    id = graph.addNode();
    graphRender.addNodeVisual(id, 30, 30);

    id = graph.addNode();
    graphRender.addNodeVisual(id, 500, 30);

    


    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "SFML Window"
    );

    /*sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(0.f, 0.f);*/

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // draw objects here
        graphRender.render(window);

        window.display();
    }

    return 0;
}
