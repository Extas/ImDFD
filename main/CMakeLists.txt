# -----------------------------------------------------
# Meta information about the this module
# -----------------------------------------------------

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
  SOURCES
  src/main.cpp)

find_package(GLFW REQUIRED)
find_package(GLAD REQUIRED)
find_package(imgui REQUIRED)

asap_add_library(imgui STATIC
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

target_link_libraries(
  ${MODULE_TARGET_NAME}
  PUBLIC
  glfw
  glad
  imgui
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
