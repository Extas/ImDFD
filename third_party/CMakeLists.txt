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
#   NAME
#   magic_enum
#   GIT_TAG
#   master
#   GITHUB_REPOSITORY
#   abdes/magic_enum
#   OPTIONS
#   "MAGIC_ENUM_OPT_INSTALL ON")
# ~~~

asap_add_package(
  NAME
  GLFW
  GIT_TAG
  3.3.8
  GITHUB_REPOSITORY
  glfw/glfw
  )

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
