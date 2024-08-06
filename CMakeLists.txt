cmake_minimum_required(VERSION 3.13)

project(image_editor
    VERSION 1.0.0
    DESCRIPTION ""
    HOMEPAGE_URL ""
    LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 20)

add_subdirectory(src/filter)
add_subdirectory(src/image)
add_subdirectory(src/format)
add_subdirectory(lib/simple_cli)

add_executable(ImageEditor main.cpp)
target_link_libraries(ImageEditor Image Format Filter simple_cli)