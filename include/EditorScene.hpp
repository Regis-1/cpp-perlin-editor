#pragma once

#include "Scene.hpp"
#include "Renderer.hpp"
#include "PerlinGenerator.hpp"

struct PerlinParams {
    int width;
    int height;
    int octaves;
    float persistence;
    int seed;

    const char* layersNames[4] = {"layer1", "layer2", "layer3", "layer4"};
    float layersThresholds[4] = {0.f, 0.f, 0.f, 0.f};
    ImVec4 layersColors[4];
    int layersIdx = 0;
};

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

    PerlinParams _perlinParams;
};
