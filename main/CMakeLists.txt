# -----------------------------------------------------
# Meta information about the this module
# -----------------------------------------------------
asap_push_module(main)

asap_declare_module(
  MODULE_NAME
  "main"
  DESCRIPTION
  "Main module for the `ImDFD` program"
  GITHUB_REPO
  "https://github.com/extas/ImDFD"
  AUTHOR_MAINTAINER
  "Extas"
  VERSION_MAJOR
  "0"
  VERSION_MINOR
  "1"
  VERSION_PATCH
  "0")

# =====================================================
# Build instructions
# =====================================================

# -----------------------------------------------------
# Main module target
# -----------------------------------------------------
set(MODULE_TARGET_NAME "ImDFD")

asap_add_executable(
  ${MODULE_TARGET_NAME}
  WARNING
  EXCEPTIONS
  SOURCES
  src/main.cpp
  src/GLFWMainWindows.cpp
  src/DearImGui.cpp
  src/ui/NodeEditerDemo.hpp
)

asap_set_language_standards(${MODULE_TARGET_NAME}
  CXX 17)

find_package(GLFW REQUIRED)
find_package(GLAD REQUIRED)
find_package(imgui REQUIRED)
find_package(imgui_node_editor REQUIRED)

asap_add_library(imgui STATIC
  WARNING
  SOURCES
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
  ${GLFW_SOURCE_DIR}/include
)

file(GLOB IMGUI_NODE_EDITOR_SRC ${imgui_node_editor_SOURCE_DIR}/*.cpp)
asap_add_library(imgui_node_editor STATIC
  WARNING
  SOURCES
  ${IMGUI_NODE_EDITOR_SRC}
)
target_link_libraries(imgui_node_editor PRIVATE imgui)
target_include_directories(imgui_node_editor PUBLIC ${imgui_node_editor_SOURCE_DIR})

target_link_libraries(
  ${MODULE_TARGET_NAME}
  PUBLIC
  glfw
  glad
  imgui
  imgui_node_editor
)

target_include_directories(${MODULE_TARGET_NAME} PRIVATE ${CMAKE_BINARY_DIR}/include)
target_include_directories(${MODULE_TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# =====================================================
# Deployment instructions
# =====================================================

# Executable
install(
  TARGETS ${MODULE_TARGET_NAME}
  RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT programs
  BUNDLE DESTINATION ${INSTALL_BIN} COMPONENT programs)

asap_pop_module(main)
