#include <iostream>
#include <SFML/Graphics.hpp>

#include "graphics/GraphRender.hpp"
#include "math/graph/Graph.hpp"

using namespace std;

int main() {
    math::graph::Graph graph;
    graphics::GraphRender graphRender;
    graphRender.setDrawableStructure(&graph);

    int id;
    id = graph.addNode();
    graphRender.addNodeVisual(id, 100, 100);

    id = graph.addNode();
    graphRender.addNodeVisual(id, 30, 30);

    id = graph.addNode();
    graphRender.addNodeVisual(id, 200, 30);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);


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
