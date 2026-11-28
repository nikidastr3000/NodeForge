#pragma once

#include <optional>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "graphics/GraphRender.hpp"
#include "math/graph/Graph.hpp"

namespace app {

enum class AppMode {
    GraphEdit,
    TreeAlgorithm
};

class App {
private:
    sf::RenderWindow window;
    sf::View canvasView;
    sf::Clock deltaClock;
    bool isImGuiInitialized = false;

    AppMode mode = AppMode::GraphEdit;
    math::graph::Graph graph;
    graphics::GraphRender graphRender;

    // Состояние интеракции пользователя на холсте
    std::optional<int> selectedNodeId;
    // TODO: Позже добавить hoveredNodeId, draggedNodeId и экземпляр активного дерева (например, AVLTree)

public:
    App();
    ~App();

    // App владеет окном SFML и контекстом ImGui-SFML — копирование запрещено
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    int run();

private:
    bool init();
    void shutdown();

    // Временная тестовая сцена (перенесена из main.cpp для проверки работы каркаса)
    void setupInitialScene();

    // Основные этапы одного кадра
    void processEvents();
    void update(sf::Time dt);
    void buildUI();
    void render();

    // Вспомогательные апдейты
    void updateCamera(sf::Time dt);

    // Заготовки обработчиков ввода на холсте (вызываются с учётом WantCaptureMouse / WantCaptureKeyboard)
    void handleMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseEvent);
    void handleMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseEvent);
    void handleMouseMoved(const sf::Event::MouseMoveEvent& mouseEvent);
    void handleKeyPressed(const sf::Event::KeyEvent& keyEvent);
};

} // namespace app
