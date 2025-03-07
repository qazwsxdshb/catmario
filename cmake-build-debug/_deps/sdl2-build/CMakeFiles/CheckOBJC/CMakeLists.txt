cmake_minimum_required(VERSION 3.30.5)
set(CMAKE_MODULE_PATH "/Users/easn/catmario/PTSD/lib/sdl2/cmake")
project(CheckOBJC OBJC)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/result.cmake"
  "set(CMAKE_OBJC_COMPILER \"${CMAKE_OBJC_COMPILER}\")\n"
  
  )