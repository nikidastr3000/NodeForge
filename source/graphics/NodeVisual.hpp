#pragma once

namespace graphics {

struct NodeVisual {
    float x = 0.0f;
    float y = 0.0f;
    float radius = 0.0f;

    // TODO: На Class Diagram указано поле `+ color: enum` без имени перечисления и списка значений.
    // Требуется определить конкретный тип enum (или заменить на sf::Color из SFML 2.5).
};

} // namespace graphics
