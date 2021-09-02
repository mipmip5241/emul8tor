cmake_minimum_required(VERSION 3.16.3)

project(emul8tor VERSION 1.0.0)


set(CMAKE_CXX_STANDARD)
set(SFML_LIBS sfml-system sfml-graphics sfml-window)

include_directories(${include_dir}/include)

set(SOURCE_FILES 
    ../src/Core.cpp
    ../src/Game.cpp
    ../src/InputHandler.cpp)

if(SFML_LIBS)
    add_executable(emu ${SOURCE_FILES})
    target_link_libraries(emu ${SFML_LIBS})
else()
    message("[ERROR]: SFML not found.\n")
endif()
