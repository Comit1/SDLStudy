
add_executable(load_image load_image.cpp)

target_link_sdl(load_image)
target_link_sdl_image(load_image)