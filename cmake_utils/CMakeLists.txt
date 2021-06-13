message(${CMAKE_CURRENT_SOURCE_DIR})

macro(init_path)
    message("init library path")
    set(SDL_DIR "/usr/local/Cellar/sdl2/2.0.14_1")
    set(SDL_IMAGE_DIR "/usr/local/Cellar/sdl2_image/2.0.5")
endmacro()

macro(link_sdl)
    message("link sdl library and path is ${SDL_DIR}")
    include_directories(${SDL_DIR}/include/SDL2)
    link_directories(${SDL_DIR}/lib)
endmacro()

macro(link_sdl_image)
    message("link sdl image library and path is ${SDL_IMAGE_DIR}")
    include_directories("${SDL_IMAGE_DIR}/include/SDL2")
    link_directories("${SDL_IMAGE_DIR}/lib")
endmacro()

macro(target_link_sdl name)
    message("${name} link sdl")
    target_link_libraries(${name} SDL2)
endmacro()

macro(target_link_sdl_image name)
    message("${name} link sdl image")
    target_link_libraries(${name} SDL2_image)
endmacro()