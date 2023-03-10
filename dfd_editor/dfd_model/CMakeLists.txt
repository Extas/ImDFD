# -----------------------------------------------------
# Meta information about the module
# -----------------------------------------------------
asap_push_module(dfd_model)

asap_declare_module(
  MODULE_NAME
  "dfd_model"
  DESCRIPTION
  "Data structures for DFD modeling"
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

# -----------------------------------------------------
# Main module target
# -----------------------------------------------------
set(MODULE_TARGET_NAME "dfd_model")

file(GLOB_RECURSE SOURCES
  CONFIGURE_DEPENDS
  src/*.cpp
  include/*.h)

asap_add_library(
  ${MODULE_TARGET_NAME} STATIC WARNING SOURCES

  ${SOURCES}
)

asap_set_language_standards(${MODULE_TARGET_NAME} CXX 17)

target_link_libraries(${MODULE_TARGET_NAME}
  PRIVATE
  logging
)

target_include_directories(
  ${MODULE_TARGET_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(${MODULE_TARGET_NAME}
  PRIVATE ${CMAKE_BINARY_DIR}/include)
target_include_directories(${MODULE_TARGET_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# -----------------------------------------------------
# Tests
# -----------------------------------------------------
if(ASAP_BUILD_TESTS)
  # add_subdirectory(test)
endif()

asap_pop_module(dfd_model)
