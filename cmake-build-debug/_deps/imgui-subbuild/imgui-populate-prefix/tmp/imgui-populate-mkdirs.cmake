# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/easn/catmario/PTSD/lib/imgui")
  file(MAKE_DIRECTORY "/Users/easn/catmario/PTSD/lib/imgui")
endif()
file(MAKE_DIRECTORY
  "/Users/easn/catmario/cmake-build-debug/_deps/imgui-build"
  "/Users/easn/catmario/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix"
  "/Users/easn/catmario/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/tmp"
  "/Users/easn/catmario/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp"
  "/Users/easn/catmario/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/src"
  "/Users/easn/catmario/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/easn/catmario/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/easn/catmario/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
