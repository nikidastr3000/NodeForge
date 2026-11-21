#pragma once
#include "math/common/Constants.hpp"

namespace graphics {

struct NodeVisual {
    float x = 0.0f;
    float y = 0.0f;
    float radius = 0.0f;

    NodeVisual() {
        x = DEFAULT_NODE_X_COORD;
        y = DEFAULT_NODE_Y_COORD;
        radius = DEFAULT_NODE_RADIUS;
    }

    NodeVisual(float x, float y) {
        this->x = x;
        this->y = y;
        radius = DEFAULT_NODE_RADIUS;
    }

    NodeVisual(float x, float y, float radius) {
        this->x = x;
        this->y = y;
        this->radius = radius;
    }

    // TODO: На Class Diagram указано поле `+ color: enum` без имени перечисления и списка значений.
    // Требуется определить конкретный тип enum (или заменить на sf::Color из SFML 2.5).
};

} // namespace graphics
