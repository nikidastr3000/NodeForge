#pragma once
#include "graphics/Constants.hpp"

namespace graphics {

struct NodeVisual {
    float x = DEFAULT_NODE_X_COORD;
    float y = DEFAULT_NODE_Y_COORD;
    float radius = DEFAULT_NODE_RADIUS;

    NodeVisual() = default;

    NodeVisual(float x, float y, float radius = DEFAULT_NODE_RADIUS)
        : x(x), y(y), radius(radius){}

    // TODO: На Class Diagram указано поле `+ color: enum` без имени перечисления и списка значений.
    // Требуется определить конкретный тип enum (или заменить на sf::Color из SFML 2.5).
};

} // namespace graphics
