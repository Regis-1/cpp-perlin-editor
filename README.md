# C++ Perlin noise editor
## Description
This program allows users to create, customize and preview the Perlin noise map. It is possible to change the dimensions of created texture, number of octaves and the persistence coefficient. Generation is pseudorandom so there is also seed parameter to adjust.\
Besides fundamental generation there is also "Coloring" section that let users to add color layers with specific thresholds and color the noise map.

![Example map](https://github.com/Regis-1/cpp-perlin-editor/assets/59539717/c2f8da84-4f6a-4260-b39e-0a79c19d4eb6)

## To be implemented
- exporting the noise map (with created color palette if there is any)
- adding utilities like zooming in/out or adding marking of generated map

## How to run it
This program uses CMake as a build tool and it is self-contained with external libraries. In that case you only need the C++ compiler and the CMake installed on your machine.

### Steps:
1. Clone the repository with ```git clone https://github.com/Regis-1/cpp-perlin-noise``` or via ZIP download.
2. Make ```build``` directory and open CMake program.
3. Generate makefiles to your preferred build tool. NOTE: If you don't want to search shared library files in ```extlibs``` directories just check the ```SDL_STATIC``` and uncheck the ```SDL_SHARED``` options in CMake.

![Cmake](https://github.com/Regis-1/cpp-perlin-editor/assets/59539717/16f081e5-2727-40a7-b8a8-372c77ed591a)

4. Use the build tool to make the executable. If you have selected the ```SDL_SHARED``` option you will need to copy the dll files to the directory with executable.
5. Run the ```perlin_editor``` executable.

## Used libraries
- SDL - https://github.com/libsdl-org/SDL
- Dear ImGui - https://github.com/ocornut/imgui
