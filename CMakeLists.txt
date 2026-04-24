cmake_minimum_required(VERSION 3.26)
project(ICY_TOWER CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/x86_64-w64-mingw32")
set(SDL2_IMAGE_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2_image/x86_64-w64-mingw32")

set(SDL2_INCLUDE_DIR "${SDL2_BASE_PATH}/include/SDL2")
set(SDL2_IMAGE_INCLUDE_DIR "${SDL2_IMAGE_BASE_PATH}/include/SDL2")

set(SDL2_LIBRARY "${SDL2_BASE_PATH}/lib/libSDL2.dll.a")
set(SDL2_MAIN_LIBRARY "${SDL2_BASE_PATH}/lib/libSDL2main.a")
set(SDL2_IMAGE_LIBRARY "${SDL2_IMAGE_BASE_PATH}/lib/libSDL2_image.dll.a")

add_executable(ICY_TOWER
        main.cpp
        Player.cpp
        Constants.h
)

target_include_directories(ICY_TOWER PRIVATE ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

target_link_libraries(ICY_TOWER
        -lmingw32
        ${SDL2_MAIN_LIBRARY}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
)
