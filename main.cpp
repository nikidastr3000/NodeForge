#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {



    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "SFML Window"
    );

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(0.f, 0.f);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // draw objects here
        window.draw(circle);

        window.display();
    }

    return 0;
}
