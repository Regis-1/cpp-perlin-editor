#include "EditorScene.hpp"
#include "RenderUtils.hpp"

#include <iostream>
#include <chrono>

#include "SDL3/SDL.h"

EditorScene::EditorScene() {
    _perlinParams.width = 600;
    _perlinParams.height = 400;
    _perlinGen.SetDimensions(_perlinParams.width, _perlinParams.height);
    _perlinParams.octaves = 5; _perlinParams.persistence = 0.5;
    _perlinParams.seed = 0;
}

EditorScene::~EditorScene() {
    delete [] _pixels; _pixels = nullptr;
}

void EditorScene::ProcessEvents(App* app, SDL_Event& event) {
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            app->Quit();
        if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            app->Quit();
        if (event.type == SDL_EVENT_WINDOW_RESIZED)
            Renderer::GetInstance()->SetViewport({0, 0, event.window.data1, event.window.data2});
    }
}

void EditorScene::Update() {
    // generation
    if (_generatePerlin) {
        if (_pixels != nullptr)
            delete [] _pixels; _pixels = nullptr; // clean the _pixel pointer

        _perlinGen.SetDimensions(_perlinParams.width, _perlinParams.height);

        _pixels = new double[_perlinParams.width*_perlinParams.height];
        auto start = std::chrono::high_resolution_clock::now();
        _perlinGen.Generate2D(_pixels, _perlinParams.octaves, _perlinParams.persistence);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        std::cout << "Noise values generation: " << duration.count() << "us" << std::endl;
        _generatePerlin = false;
    }

    // creating texture
    if (_generateTexture) {
        if (_perlinTexture != nullptr) {
            Renderer::GetInstance()->DestroyTexture(_perlinTexture);
            _perlinTexture = nullptr;
        }

        uint8_t sdlPixels[_perlinParams.width*_perlinParams.height];
        for (int i = 0; i < _perlinParams.width*_perlinParams.height; i++)
            sdlPixels[i] = static_cast<uint8_t>(_pixels[i]*255);


        SDL_Surface* surface = Renderer::GetInstance()->CreateSurfaceFrom(
                sdlPixels, _perlinParams.width, _perlinParams.height,
                _perlinParams.width, SDL_PIXELFORMAT_INDEX8);
        _perlinTexture = Renderer::GetInstance()->CreateTextureFromSurface(surface,
                _perlinParams.paletteIdx);

        _generateTexture = false;
    }
}

void EditorScene::Render() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    
    //ImGui::ShowDemoWindow();
    MakeImGuiWindow();

    ImGui::Render();

    //normal rendering
    if (_perlinTexture != nullptr) {
        Renderer::GetInstance()->RenderTexture(_perlinTexture);
    }

    // grid at the end to render it on top of all other things
    if (_showGrid) {
        RenderUtils::RenderGrid();
    }

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
}

// ImGui window
void EditorScene::MakeImGuiWindow() {
    ImGui::Begin("Perlin Editor");
    if (ImGui::CollapsingHeader("Base parameters")) {
        ImGui::DragInt("Width", &_perlinParams.width, 1, 1, UINT_MAX);
        ImGui::DragInt("Height", &_perlinParams.height, 1, 1, UINT_MAX);
        ImGui::DragInt("Seed", &_perlinParams.seed, 1, 0, UINT_MAX);
        ImGui::DragInt("Octaves", &_perlinParams.octaves, 0.5f, 1, 32);
        ImGui::DragFloat("Persistence", &_perlinParams.persistence, 0.001f, 0.001f, 0.999f);
        if (ImGui::Button("Generate")) {
            _perlinGen.Seed(_perlinParams.seed);
            _generatePerlin = true;
            _generateTexture = true;
        }
    }
    if (ImGui::CollapsingHeader("Coloring")) {
        int& colLayersIxd = _perlinParams.layersIdx;
        if (ImGui::Button("Add layer")) {
            _perlinParams.topIdx++;
            int newIdx = _perlinParams.topIdx;
            _perlinParams.layersNames.push_back("layer" + std::to_string(newIdx));
            _perlinParams.layersThresholds.push_back(0.f);
            _perlinParams.layersColors.push_back(ImVec4());
        }
        if (ImGui::Button("Remove layer")) {
            auto delNamesIdx = _perlinParams.layersNames.begin() + colLayersIxd;
            auto delThresholdsIdx = _perlinParams.layersThresholds.begin() + colLayersIxd;
            auto delColorsIdx = _perlinParams.layersColors.begin() + colLayersIxd;
            _perlinParams.layersNames.erase(delNamesIdx);
            _perlinParams.layersThresholds.erase(delThresholdsIdx);
            _perlinParams.layersColors.erase(delColorsIdx);
        }
        if (ImGui::BeginListBox("Layers")) {
            for (int i = 0; i < _perlinParams.layersNames.size(); i++) {
                const bool isSelected = (colLayersIxd == i);
                if (ImGui::Selectable(_perlinParams.layersNames[i].c_str(), isSelected))
                    colLayersIxd = i;

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        if (_perlinParams.layersNames.size() > 0) {
            ImGui::SliderFloat("Threshold", &_perlinParams.layersThresholds[colLayersIxd], 0.f, 1.f);
            ImGui::ColorEdit3("Color", (float*)&_perlinParams.layersColors[colLayersIxd]);
        }
        if (ImGui::Button("Color noise")) {
            if (_perlinParams.layersNames.size() > 0) {
                Renderer::GetInstance()->CreateLayeredPalette(_perlinParams.layersThresholds,
                        _perlinParams.layersColors);
                _perlinParams.paletteIdx = 1;
                _generateTexture = true;
            }
        }
        if (ImGui::Button("Use grayscale")) {
            _perlinParams.paletteIdx = 0;
            _generateTexture = true;
        }
    }
    if (ImGui::CollapsingHeader("Utilities")) {
        ImGui::Checkbox("Grid", &_showGrid);
    }
    ImGui::End();
}
