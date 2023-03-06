# -----------------------------------------------------
# Meta information about the this module
# -----------------------------------------------------
asap_push_module(logging)

asap_declare_module(
  MODULE_NAME
  "logging"
  DESCRIPTION
  "Logging utilities and functions"
  GITHUB_REPO
  "https://github.com/extas/ImDFD"
  AUTHOR_MAINTAINER
  "The Author"
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

set(MODULE_TARGET_NAME "logging")

asap_add_library(
  ${MODULE_TARGET_NAME} STATIC
  WARNING
  SOURCES
  # Sources
  src/logger.cpp)

asap_set_language_standards(${MODULE_TARGET_NAME}
  CXX 17)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${MODULE_TARGET_NAME} PRIVATE spdlog::spdlog)

target_include_directories(${MODULE_TARGET_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

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

asap_pop_module(logging)
