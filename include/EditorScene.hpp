#pragma once

#include <vector>
#include <string>

#include "Scene.hpp"
#include "Renderer.hpp"
#include "PerlinGenerator.hpp"

struct PerlinParams {
    int width;
    int height;
    int octaves;
    float persistence;
    int seed;

    int layersIdx = 0;
    int topIdx = 0;
    int paletteIdx = 0;
    std::vector<std::string> layersNames;
    std::vector<float> layersThresholds;
    std::vector<ImVec4> layersColors;
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
    bool _generateTexture{true};
    PerlinGenerator _perlinGen;
    double* _pixels{nullptr};
    SDL_Texture* _perlinTexture;

    PerlinParams _perlinParams;
};
