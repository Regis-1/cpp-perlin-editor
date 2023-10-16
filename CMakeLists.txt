cmake_minimum_required(VERSION 3.25)

project(perlin_editor)

add_subdirectory(extlibs)

add_executable(${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/App.cpp
    ${CMAKE_SOURCE_DIR}/src/EditorScene.cpp
    ${CMAKE_SOURCE_DIR}/src/Renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/PerlinGenerator.cpp
    )

#imgui sources
target_sources(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/src/imgui.cpp
    ${CMAKE_SOURCE_DIR}/src/imgui_impl_sdl3.cpp
    ${CMAKE_SOURCE_DIR}/src/imgui_impl_sdlrenderer3.cpp
    ${CMAKE_SOURCE_DIR}/src/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/src/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/src/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/src/imgui_widgets.cpp
    )

target_link_libraries(${PROJECT_NAME}
    PUBLIC SDL3-static
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PUBLIC ${CMAKE_SOURCE_DIR}/extlibs/SDL/include
    )
