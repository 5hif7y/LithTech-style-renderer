cmake_minimum_required(VERSION 3.10)
project(Modular2DEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(engine)
add_subdirectory(renderers/OGL4REN)
add_subdirectory(game)

