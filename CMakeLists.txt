cmake_minimum_required(VERSION 3.16)
project(NodeForge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(NodeForge
    main.cpp
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

target_link_libraries(NodeForge PRIVATE sfml-graphics sfml-window sfml-system)

