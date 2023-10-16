#pragma once

#include "Scene.hpp"
#include "Renderer.hpp"
#include "PerlinGenerator.hpp"

class EditorScene : public Scene {
public:
    EditorScene();
    ~EditorScene();

    void Render() override;
    void ProcessEvents(App* app, SDL_Event& event) override;
    void Update() override;

private:
    bool _showGrid{true};
    PerlinGenerator _perlinGen{400, 300, 13};
};
