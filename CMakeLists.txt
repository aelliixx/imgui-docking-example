cmake_minimum_required(VERSION 3.24)
project(real_engine)
#add_compile_options(-Werror -Wextra -Wall -Wpedantic)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src/libs)

set(SOURCE_FILES src/main.cpp         
        src/Engine/Engine.cpp
        src/Engine/Engine.h
        src/Engine/Window/Window.cpp
        src/Engine/Window/Window.h
        src/Windows/Properties/PropertiesTest.cpp
        src/Windows/Properties/Properties.h
        src/Engine/Window/Dockspace.cpp
        src/Engine/Window/Dockspace.h
        src/Windows/Viewport/Viewport.cpp) 
set(IMGUI_SOURCES 
        src/libs/imgui/imgui.h
        src/libs/imgui/imgui.cpp
        src/libs/imgui/imgui_draw.cpp
        src/libs/imgui/imgui_tables.cpp
        src/libs/imgui/imgui_widgets.cpp
        src/libs/imgui/imgui_demo.cpp
        src/libs/imgui/imgui_impl_sdl2.h
        src/libs/imgui/imgui_impl_sdl2.cpp
        src/libs/imgui/imgui_impl_opengl3.h
        src/libs/imgui/imgui_impl_opengl3.cpp
        src/libs/imgui/imgui_impl_opengl3_loader.h

)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCES})
        

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} Colour Print ${SDL2_LIBRARIES} OpenGL::OpenGL)
