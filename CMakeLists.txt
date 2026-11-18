cmake_minimum_required(VERSION 3.16)
project(NodeForge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(NodeForge
    main.cpp
    source/math/AVLTree.cpp
    source/math/BinarySearchTree.cpp
    source/math/BinaryTree.cpp
    source/math/BinaryTreeNode.cpp
    source/math/Edge.cpp
    source/math/Graph.cpp
    source/math/IDrawableStructure.cpp
    source/math/Node.cpp
    source/math/NodeValue.cpp
    source/math/Tree.cpp
    source/math/TreeNode.cpp
    source/graphics/GraphRender.cpp
    source/graphics/NodeVisual.cpp
)

target_include_directories(NodeForge PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/source/math
    ${CMAKE_CURRENT_SOURCE_DIR}/source/graphics
)

target_link_libraries(NodeForge PRIVATE sfml-graphics sfml-window sfml-system)

