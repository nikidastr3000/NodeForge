#include "app/App.hpp"

#include <iostream>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

namespace app {

namespace {
constexpr unsigned int DEFAULT_WINDOW_WIDTH = 800;
constexpr unsigned int DEFAULT_WINDOW_HEIGHT = 600;
constexpr unsigned int DEFAULT_FPS_LIMIT = 60;

constexpr float DEFAULT_CAMERA_SPEED = 300.f;    //in pixels/second
} // anonym namespace - the variables can be seen only in this file

App::App()
    : window(sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), "NodeForge"),
      canvasView(window.getDefaultView()) {
    window.setFramerateLimit(DEFAULT_FPS_LIMIT);
    graphRender.setDrawableStructure(&graph);
}

App::~App() {
    shutdown();
}

int App::run() {
    if (!init()) {
        return 1;
    }

    setupInitialScene();
    deltaClock.restart();

    while (window.isOpen()) {
        processEvents();

        const sf::Time dt = deltaClock.restart();
        update(dt);
        buildUI();
        render();
    }

    shutdown();
    return 0;
}

bool App::init() {
    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui-SFML\n";
        return false;
    }

    isImGuiInitialized = true;
    return true;
}

void App::shutdown() {
    if (isImGuiInitialized) {
        ImGui::SFML::Shutdown();
        isImGuiInitialized = false;
    }
}

void App::setupInitialScene() {
    int id = graph.addNode();
    graphRender.addNodeVisual(id, 100.f, 100.f);

    id = graph.addNode();
    graphRender.addNodeVisual(id, 30.f, 30.f);

    id = graph.addNode();
    graphRender.addNodeVisual(id, 200.f, 30.f);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);

    selectedNodeId = 0;
}

void App::processEvents() {
    sf::Event event{};

    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window, event);

        // 1. Системные события окна обрабатываются всегда
        if (event.type == sf::Event::Closed) {
            window.close();
            continue;
        }

        if (event.type == sf::Event::Resized) {
            canvasView.setSize(
                static_cast<float>(event.size.width),
                static_cast<float>(event.size.height)
            );
        }

        // 2. Отпускание кнопок мыши обрабатывается всегда, чтобы не «залипал» drag-and-drop
        if (event.type == sf::Event::MouseButtonReleased) {
            handleMouseButtonReleased(event.mouseButton);
        }

        const ImGuiIO& io = ImGui::GetIO();

        // 3. События мыши на холсте — только если курсор не над UI
        if (!io.WantCaptureMouse) {
            if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseButtonPressed(event.mouseButton);
            } else if (event.type == sf::Event::MouseMoved) {
                handleMouseMoved(event.mouseMove);
            }
            // TODO: Добавить обработку sf::Event::MouseWheelScrolled для зума canvasView
        }

        // 4. Горячие клавиши холста — только если фокус не в поле ввода UI
        if (!io.WantCaptureKeyboard) {
            if (event.type == sf::Event::KeyPressed) {
                handleKeyPressed(event.key);
            }
        }
    }
}

void App::update(sf::Time dt) {
    ImGui::SFML::Update(window, dt);


    updateCamera(dt);


    // TODO: Обновление таймеров и плавных анимаций алгоритмов с использованием dt.asSeconds()
}

void App::buildUI() {
    ImGui::Begin("NodeForge");
    ImGui::Text("Mode: %s", mode == AppMode::GraphEdit ? "Graph Editing" : "Tree Algorithm");
    ImGui::Text("Nodes: %zu", graph.getNodes().size());

    // TODO: Панель переключения режимов, ввод value, кнопки добавления/удаления и управления алгоритмами
    ImGui::End();
}

void App::render() {
    window.clear(sf::Color::White);

    window.setView(canvasView);
    graphRender.render(window, selectedNodeId);

    window.setView(window.getDefaultView());
    ImGui::SFML::Render(window);

    window.display();
}

// Вспомогательные апдейты
void App::updateCamera(sf::Time dt) {
    if (!window.hasFocus() || ImGui::GetIO().WantCaptureKeyboard) {
        return;
    }

    sf::Vector2f direction(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction.x += 1.f;

    canvasView.move(direction * DEFAULT_CAMERA_SPEED * dt.asSeconds());
}


void App::handleMouseButtonPressed(const sf::Event::MouseButtonEvent& /*mouseEvent*/) {
    // TODO: Перевести пиксели в мировые координаты через window.mapPixelToCoords(pixelPos, canvasView)
    // и обработать выбор/создание вершины или старт перетаскивания
}

void App::handleMouseButtonReleased(const sf::Event::MouseButtonEvent& /*mouseEvent*/) {
    // TODO: Сбросить состояние перетаскивания вершины / панорамирования камеры
}

void App::handleMouseMoved(const sf::Event::MouseMoveEvent& /*mouseEvent*/) {
    // TODO: Обновить hover и координаты перетаскиваемой вершины / камеры
}

void App::handleKeyPressed(const sf::Event::KeyEvent& /*keyEvent*/) {
    // TODO: Горячие клавиши холста (например, удаление выбранной вершины по Delete/BackSpace)
}

} // namespace app
