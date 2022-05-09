cmake_minimum_required(VERSION 3.1)

project(Pong)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra)
if (WIN32)
    set( SFML_STATIC_LIBRARIES TRUE )
    set ( SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML/")
endif(WIN32)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

add_executable(Pong main.cpp Paddle.cpp Paddle.h Ball.cpp Ball.h)

target_link_libraries(Pong sfml-graphics sfml-audio)

