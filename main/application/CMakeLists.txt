# -----------------------------------------------------
# Meta information about the this module
# -----------------------------------------------------
asap_push_module(application)

asap_declare_module(
  MODULE_NAME
  "application"
  DESCRIPTION
  "Main application for the ImDFD program"
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
set(MODULE_TARGET_NAME "application")

file(GLOB_RECURSE SOURCES
  CONFIGURE_DEPENDS
  src/*.cpp
  include/*.h)

asap_add_library(
  ${MODULE_TARGET_NAME} STATIC WARNING EXCEPTIONS SOURCES

  ${SOURCES})

asap_set_language_standards(${MODULE_TARGET_NAME} CXX 17)

target_link_libraries(
  ${MODULE_TARGET_NAME}
  PRIVATE
  imgui
  ImDFD::logging)

find_package(stb REQUIRED)
target_include_directories(${MODULE_TARGET_NAME} PRIVATE ${stb_SOURCE_DIR})
target_include_directories(${MODULE_TARGET_NAME} PRIVATE ${CMAKE_BINARY_DIR}/include)
target_include_directories(${MODULE_TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(
  ${MODULE_TARGET_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# configure_file(
# include/application/config.h.in
# ${CMAKE_CURRENT_BINARY_DIR}/include/application/config.h
# )
if(WIN32)
  set(_DXSDK_Dir ${CMAKE_SOURCE_DIR}/third_party/DXSDK)
  set(_DXSDK_Arch x86)

  if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    set(_DXSDK_Arch x64)
  endif()

  add_library(dxerr STATIC ${_DXSDK_Dir}/src/dxerr.cpp)
  target_include_directories(dxerr PUBLIC "${_DXSDK_Dir}/include")
  set_property(TARGET dxerr PROPERTY FOLDER "external")

  add_library(d3dx11 UNKNOWN IMPORTED)
  set_target_properties(d3dx11 PROPERTIES
    IMPORTED_LOCATION "${_DXSDK_Dir}/lib/${_DXSDK_Arch}/d3dx11.lib"
    IMPORTED_LOCATION_DEBUG "${_DXSDK_Dir}/lib/${_DXSDK_Arch}/d3dx11d.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${_DXSDK_Dir}/include"
    INTERFACE_LINK_LIBRARIES "$<$<CONFIG:Debug>:dxerr>"
  )

  target_link_libraries(application PRIVATE d3d11.lib d3dcompiler.lib d3dx11)
else()
  # find_package(OpenGL REQUIRED)
  # find_package(glfw REQUIRED)
  if(APPLE)
    target_link_libraries(application PRIVATE
      "-framework CoreFoundation"
      "-framework Cocoa"
      "-framework IOKit"
      "-framework CoreVideo"
    )
  endif()
endif()

# -----------------------------------------------------
# Tests
# -----------------------------------------------------
if(ASAP_BUILD_TESTS)
  # add_subdirectory(test)
endif()

asap_pop_module(application)
