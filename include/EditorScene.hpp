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
    bool _showGrid{false};
    bool _oneGen{true};
    PerlinGenerator _perlinGen{600, 600};
    double* _pixels{nullptr};
};
