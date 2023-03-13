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

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)
asap_add_executable(
  ${MODULE_TARGET_NAME}
  WARNING
  EXCEPTIONS
  SOURCES
  ${SOURCES})

asap_set_language_standards(${MODULE_TARGET_NAME}
  CXX 17)

target_link_libraries(
  ${MODULE_TARGET_NAME}
  PRIVATE
  ui
  dfd_editor
  logging
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
