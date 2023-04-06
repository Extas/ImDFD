# -----------------------------------------------------
# Meta information about the this module
# -----------------------------------------------------
asap_push_module(imgui)

asap_declare_module(
        MODULE_NAME
        "imgui"
        DESCRIPTION
        "The libraries about imgui"
        GITHUB_REPO
        "https://github.com/extas/ImDFD"
        AUTHOR_MAINTAINER
        "Extas"
        VERSION_MAJOR
        "1"
        VERSION_MINOR
        "0"
        VERSION_PATCH
        "0")

# =====================================================
# Build instructions
# =====================================================

# -----------------------------------------------------
# Main module target
# -----------------------------------------------------
set(MODULE_TARGET_NAME "imgui")

find_package(GLFW REQUIRED)
find_package(glad REQUIRED)
find_package(imgui REQUIRED)

set(GLAD_PROFILE "core" CACHE STRING "" FORCE)

asap_add_library(${MODULE_TARGET_NAME} STATIC
        WARNING
        SOURCES
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
        )

target_link_libraries(${MODULE_TARGET_NAME} PUBLIC glfw glad)

target_include_directories(${MODULE_TARGET_NAME} PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${imgui_SOURCE_DIR}/misc/cpp
        ${GLFW_SOURCE_DIR}/include)

asap_pop_module(imgui)

# -----------------------------------------------------
# imgui_node_editor
# -----------------------------------------------------
asap_push_module(node_editor)

asap_declare_module(
        MODULE_NAME
        "node_editor"
        DESCRIPTION
        "The libraries about imgui"
        GITHUB_REPO
        "https://github.com/extas/ImDFD"
        AUTHOR_MAINTAINER
        "Extas"
        VERSION_MAJOR
        "1"
        VERSION_MINOR
        "0"
        VERSION_PATCH
        "0")

set(MODULE_TARGET_NAME "node_editor")

find_package(imgui_node_editor REQUIRED)
file(GLOB IMGUI_NODE_EDITOR_SRC CONFIGURE_DEPENDS ${imgui_node_editor_SOURCE_DIR}/*.cpp)
asap_add_library(node_editor STATIC
        WARNING
        SOURCES
        ${IMGUI_NODE_EDITOR_SRC}
        )
target_link_libraries(node_editor PRIVATE imgui)
target_include_directories(node_editor PUBLIC
        ${imgui_node_editor_SOURCE_DIR}/)

asap_pop_module(node_editor)
