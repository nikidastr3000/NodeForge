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

constexpr float DOUBLE_CLICK_MAX_SECONDS = 0.35f;
constexpr int DOUBLE_CLICK_MAX_DISTANCE_PX = 6;

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

    if (interactionState == InteractionState::CreatingEdge && interactionNodeId.has_value()) {
        const sf::Vector2f mouseWorldPos = window.mapPixelToCoords(
            sf::Mouse::getPosition(window),
            canvasView
        );
        graphRender.renderPreviewEdge(window, interactionNodeId.value(), mouseWorldPos);
    }

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


void App::handleMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseEvent) {
    // TODO: Перевести пиксели в мировые координаты через window.mapPixelToCoords(pixelPos, canvasView)
    // и обработать выбор/создание вершины или старт перетаскивания

    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(
        sf::Vector2i(mouseEvent.x, mouseEvent.y),
        canvasView
    );
    std::optional<int> hit = graphRender.getNodeAt(mouseWorldPos);

    const bool isShiftPressed =
    sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

    const bool isEdgeGesture =
        (mouseEvent.button == sf::Mouse::Right) ||
        (mouseEvent.button == sf::Mouse::Left && isShiftPressed);

    if (isEdgeGesture) {
        hasPendingEmptyClick = false;

        if (mode == AppMode::GraphEdit && hit.has_value()) {
            interactionState = InteractionState::CreatingEdge;
            interactionNodeId = hit;
        }
        return;
    }

    if (mouseEvent.button == sf::Mouse::Left) {
        if (hit.has_value()) {
            selectedNodeId = hit;
            interactionNodeId = hit;
            interactionState = InteractionState::DraggingNode;
            dragOffset = graphRender.getNodePosition(hit.value()) - mouseWorldPos;

            hasPendingEmptyClick = false;
        } else {
            interactionState = InteractionState::Idle;
            selectedNodeId = std::nullopt;
            interactionNodeId = std::nullopt;

            const sf::Vector2i clickPixelPos(mouseEvent.x, mouseEvent.y);
            const int dx = clickPixelPos.x - lastEmptyClickPixelPos.x;
            const int dy = clickPixelPos.y - lastEmptyClickPixelPos.y;

            const bool isCloseEnough =
                (dx * dx + dy * dy) <= (DOUBLE_CLICK_MAX_DISTANCE_PX * DOUBLE_CLICK_MAX_DISTANCE_PX);
            const bool isFastEnough =
                lastEmptyClickClock.getElapsedTime().asSeconds() <= DOUBLE_CLICK_MAX_SECONDS;

            if (hasPendingEmptyClick && isCloseEnough && isFastEnough && mode == AppMode::GraphEdit) {
                const int newId = graph.addNode();
                graphRender.addNodeVisual(newId, mouseWorldPos.x, mouseWorldPos.y);
                selectedNodeId = newId;
                hasPendingEmptyClick = false;
            }
            else {
                lastEmptyClickPixelPos = clickPixelPos;
                lastEmptyClickClock.restart();
                hasPendingEmptyClick = (mode == AppMode::GraphEdit);
            }
        }
    }


}

void App::handleMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseEvent) {
    // TODO: Сбросить состояние перетаскивания вершины / панорамирования камеры

    if (interactionState == InteractionState::DraggingNode && mouseEvent.button == sf::Mouse::Left) {
        interactionState = InteractionState::Idle;
        interactionNodeId = std::nullopt;
    }

    if (interactionState == InteractionState::CreatingEdge &&
        (mouseEvent.button == sf::Mouse::Right || mouseEvent.button == sf::Mouse::Left)) {
        if (interactionNodeId.has_value() && !ImGui::GetIO().WantCaptureMouse) {
            const sf::Vector2f mouseWorldPos = window.mapPixelToCoords(
                sf::Vector2i(mouseEvent.x, mouseEvent.y),
                canvasView
            );

            const int fromId = *interactionNodeId;
            const std::optional<int> targetId = graphRender.getNodeAt(mouseWorldPos);

            if (targetId.has_value()) {
                // Исход 1: отпустили на ДРУГОЙ вершине -> toggle ребра
                if (*targetId != fromId) {
                    if (graph.hasEdge(fromId, *targetId)) {
                        graph.removeEdge(fromId, *targetId);
                    } else {
                        graph.addEdge(fromId, *targetId);
                    }
                }
                // Исход 2: отпустили на той же вершине (*targetId == fromId) -> ничего не делаем (отмена)
            } else if (createNodeOnEdgeDrop) {
                // Исход 3 (бонус для быстрой сборки деревьев):
                // отпустили на пустом месте -> создаём новую вершину и сразу соединяем
                const int newId = graph.addNode();
                graphRender.addNodeVisual(newId, mouseWorldPos.x, mouseWorldPos.y);
                graph.addEdge(fromId, newId);
                selectedNodeId = newId;
            }
        }

        interactionState = InteractionState::Idle;
        interactionNodeId = std::nullopt;
    }

}

void App::handleMouseMoved(const sf::Event::MouseMoveEvent& mouseEvent) {
    // TODO: Обновить hover и координаты перетаскиваемой вершины / камеры

    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(
        sf::Vector2i(mouseEvent.x, mouseEvent.y),
        canvasView
    );

    if (interactionState == InteractionState::DraggingNode && interactionNodeId.has_value()) {
        sf::Vector2f newPos = mouseWorldPos + dragOffset;
        graphRender.setNodePosition(interactionNodeId.value(), newPos.x, newPos.y);
    }
}

void App::handleKeyPressed(const sf::Event::KeyEvent& keyEvent) {
    // TODO: Горячие клавиши холста (например, удаление выбранной вершины по Delete/BackSpace)

    if (keyEvent.code == sf::Keyboard::Delete || keyEvent.code == sf::Keyboard::BackSpace) {
        if (!selectedNodeId.has_value() || mode != AppMode::GraphEdit) {
            return;
        }

        const int idToDelete= *selectedNodeId;
        graph.removeNode(idToDelete);
        graphRender.removeNodeVisual(idToDelete);
        selectedNodeId = std::nullopt;

        if (interactionNodeId == idToDelete) {
            interactionState = InteractionState::Idle;
            interactionNodeId = std::nullopt;
        }
    }

    if (keyEvent.code == sf::Keyboard::Escape && interactionState == InteractionState::CreatingEdge) {
        interactionState = InteractionState::Idle;
        interactionNodeId = std::nullopt;
    }
}

} // namespace app
