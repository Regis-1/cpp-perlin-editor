#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL3/SDL_opengles2.h>
#else
#include <SDL3/SDL_opengl.h>
#endif

class Scene;
#include "EditorScene.hpp"

class App {
public:
    App(std::string title, int w, int h);
    ~App();

    void Run();
    bool Valid() { return _valid; }
    void Quit() { _shouldQuit = true; }

private:
    SDL_Window* _window{nullptr};

    bool _valid{true};
    bool _shouldQuit{false};
    SDL_Event _event;

    std::vector<Scene*> _sceneStack;
};
