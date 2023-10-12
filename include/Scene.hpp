#pragma once

#include <iostream>
#include "SDL3/SDL.h"
#include "imgui_impl_sdl3.h"

class App;
#include "App.hpp"

class Scene {
public:
    Scene(){}
    ~Scene(){}

    virtual void Render() = 0;
    virtual void ProcessEvents(App* app, SDL_Event& event) = 0;
    virtual void Update() = 0;
};
