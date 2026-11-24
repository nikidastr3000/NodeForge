#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

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

    graph.removeNode(0);
    graphRender.removeNodeVisual(0);

    graph.removeNode(1);
    graphRender.removeNodeVisual(1);

    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "NodeForge"
    );
    window.setFramerateLimit(60);

    if (!ImGui::SFML::Init(window)) {
        cerr << "Failed to initialize ImGui-SFML\n";
        return 1;
    }

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("NodeForge");
        ImGui::Text("ImGui-SFML is initialized and ready.");
        ImGui::End();

        window.clear(sf::Color::White);

        // draw objects here
        graphRender.render(window);
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
