# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

message(STATUS "${ASAP_LOG_PROJECT_HIERARCHY} >> third-party modules")

# Call `asap_add_package` to add third party packages using CPM, while
# automatically adding/removing them to the project hierarchy stack.
#
# Refer to https://github.com/cpm-cmake/CPM.cmake for the full usage.
#
# Example:
# ~~~
# asap_add_package(
# NAME
# magic_enum
# GIT_TAG
# master
# GITHUB_REPOSITORY
# abdes/magic_enum
# OPTIONS
# "MAGIC_ENUM_OPT_INSTALL ON")
# ~~~
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
asap_add_package(
  NAME
  GLFW
  GIT_TAG
  3.3.8
  GITHUB_REPOSITORY
  glfw/glfw
)

set(GLAD_INSTALL OFF CACHE BOOL "" FORCE)
asap_add_package(
  NAME
  glad
  GIT_TAG
  v0.1.36
  GITHUB_REPOSITORY
  Dav1dde/glad
)

asap_add_package(
  NAME
  imgui
  GIT_TAG
  192196711a7d0d7c2d60454d42654cf090498a74 # docking branch
  GITHUB_REPOSITORY
  ocornut/imgui
)

asap_add_package(
  NAME
  imgui_node_editor
  GIT_TAG
  99ec923a39062f556ec7676fb9ba6d302d109f76
  GITHUB_REPOSITORY
  thedmd/imgui-node-editor
)

asap_add_package(
  NAME
  spdlog
  GIT_TAG
  v1.11.0
  GITHUB_REPOSITORY
  gabime/spdlog
)

asap_add_package(
  NAME
  gsl
  GIT_TAG
  v4.0.0
  GITHUB_REPOSITORY
  microsoft/GSL
)

asap_add_package(
  NAME
  stb
  GIT_TAG
  master
  GITHUB_REPOSITORY
  nothings/stb
)
