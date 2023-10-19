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
    void MakeImGuiWindow();

    bool _showGrid{false};
    bool _generatePerlin{true};
    PerlinGenerator _perlinGen;
    double* _pixels{nullptr};
    SDL_Texture* _perlinTexture;
    int _perlinWidth;
    int _perlinHeight;
    int _perlinOctaves;
    float _perlinPersistence;
    int _perlinSeed;
};
