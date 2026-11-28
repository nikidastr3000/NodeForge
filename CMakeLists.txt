cmake_minimum_required(VERSION 3.16)
project(NodeForge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include(FetchContent)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.5
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR} CACHE PATH "ImGui top-level directory" FORCE)
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "Use SFML found by parent project" FORCE)
set(IMGUI_SFML_IMGUI_DEMO ON CACHE BOOL "Build imgui_demo.cpp" FORCE)

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v2.6.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui-sfml)

# Совместимость ImGui-SFML 2.6.1 с SFML 2.6.2+ и новым AppleClang/libc++ (где удалён std::char_traits<uint8_t>)
file(READ "${imgui-sfml_SOURCE_DIR}/imgui-SFML.cpp" IMGUI_SFML_CPP_CONTENT)
if(IMGUI_SFML_CPP_CONTENT MATCHES "std::basic_string<std::uint8_t> tmp")
    string(REPLACE
        "std::basic_string<std::uint8_t> tmp = sf::Clipboard::getString().toUtf8();"
        "auto tmp = sf::Clipboard::getString().toUtf8();"
        IMGUI_SFML_CPP_CONTENT
        "${IMGUI_SFML_CPP_CONTENT}"
    )
    file(WRITE "${imgui-sfml_SOURCE_DIR}/imgui-SFML.cpp" "${IMGUI_SFML_CPP_CONTENT}")
endif()

add_executable(NodeForge
    main.cpp
    source/app/App.cpp
    source/graphics/GraphRender.cpp
    source/graphics/NodeVisual.cpp
    source/math/graph/Graph.cpp
    source/math/graph/Node.cpp
    source/math/trees/AVLTree.cpp
    source/math/trees/BinarySearchTree.cpp
    source/math/trees/BinaryTree.cpp
    source/math/trees/BinaryTreeNode.cpp
    source/math/trees/Tree.cpp
    source/math/trees/TreeNode.cpp
)

target_include_directories(NodeForge PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source
)

target_link_libraries(NodeForge PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    ImGui-SFML::ImGui-SFML
)

