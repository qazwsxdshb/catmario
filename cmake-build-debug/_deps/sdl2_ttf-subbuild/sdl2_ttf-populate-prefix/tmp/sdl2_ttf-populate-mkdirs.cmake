# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/easn/catmario/PTSD/lib/sdl2_ttf")
  file(MAKE_DIRECTORY "/Users/easn/catmario/PTSD/lib/sdl2_ttf")
endif()
file(MAKE_DIRECTORY
  "/Users/easn/catmario/cmake-build-debug/_deps/sdl2_ttf-build"
  "/Users/easn/catmario/cmake-build-debug/_deps/sdl2_ttf-subbuild/sdl2_ttf-populate-prefix"
  "/Users/easn/catmario/cmake-build-debug/_deps/sdl2_ttf-subbuild/sdl2_ttf-populate-prefix/tmp"
  "/Users/easn/catmario/cmake-build-debug/_deps/sdl2_ttf-subbuild/sdl2_ttf-populate-prefix/src/sdl2_ttf-populate-stamp"
  "/Users/easn/catmario/cmake-build-debug/_deps/sdl2_ttf-subbuild/sdl2_ttf-populate-prefix/src"
  "/Users/easn/catmario/cmake-build-debug/_deps/sdl2_ttf-subbuild/sdl2_ttf-populate-prefix/src/sdl2_ttf-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/easn/catmario/cmake-build-debug/_deps/sdl2_ttf-subbuild/sdl2_ttf-populate-prefix/src/sdl2_ttf-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/easn/catmario/cmake-build-debug/_deps/sdl2_ttf-subbuild/sdl2_ttf-populate-prefix/src/sdl2_ttf-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
