#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {

        if (__cplusplus == 202002L)
            std::cout << "C++20\n";
        else if (__cplusplus == 201703L)
            std::cout << "C++17\n";
        else if (__cplusplus == 201402L)
            std::cout << "C++14\n";
        else if (__cplusplus == 201103L)
            std::cout << "C++11\n";
        else
            std::cout << "C++98 or older (" << __cplusplus << ")\n";


    cout << "Hello, World!" << endl;

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
