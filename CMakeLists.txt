cmake_minimum_required(VERSION 3.15)
project(SDL)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(cmake_utils)

init_path()
link_sdl()
link_sdl_image()

add_executable(SDL main.cpp)

target_link_sdl(SDL)

add_subdirectory("load_image")
add_subdirectory("load_yuv")
add_subdirectory("play_pcm")
