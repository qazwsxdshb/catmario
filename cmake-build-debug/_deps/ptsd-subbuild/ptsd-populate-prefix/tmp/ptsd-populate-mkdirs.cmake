# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/easn/catmario/PTSD")
  file(MAKE_DIRECTORY "/Users/easn/catmario/PTSD")
endif()
file(MAKE_DIRECTORY
  "/Users/easn/catmario/cmake-build-debug/_deps/ptsd-build"
  "/Users/easn/catmario/cmake-build-debug/_deps/ptsd-subbuild/ptsd-populate-prefix"
  "/Users/easn/catmario/cmake-build-debug/_deps/ptsd-subbuild/ptsd-populate-prefix/tmp"
  "/Users/easn/catmario/cmake-build-debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src/ptsd-populate-stamp"
  "/Users/easn/catmario/cmake-build-debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src"
  "/Users/easn/catmario/cmake-build-debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src/ptsd-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/easn/catmario/cmake-build-debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src/ptsd-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/easn/catmario/cmake-build-debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src/ptsd-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
