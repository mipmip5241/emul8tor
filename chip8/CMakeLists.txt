cmake_minimum_required(VERSION 3.16.3)

project(emul8tor VERSION 1.0.0)

set(SFML_LIBS sfml-system sfml-graphics sfml-window)

set(HEADER_FILES include/Core.h include/InputHandler.h)

set(SOURCE_FILES src/Core.cpp src/Game.cpp src/InputHandler.cpp)

add_executable(chip ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(chip PRIVATE ${include})

target_link_libraries(chip ${SFML_LIBS})