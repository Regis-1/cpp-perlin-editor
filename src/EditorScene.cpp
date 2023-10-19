#include "EditorScene.hpp"
#include "RenderUtils.hpp"

#include <iostream>
#include <chrono>

#include "SDL3/SDL.h"

EditorScene::EditorScene() {
    _perlinWidth = 600;
    _perlinHeight = 400;
    _perlinGen.SetDimensions(_perlinWidth, _perlinHeight);
    _perlinOctaves = 5; _perlinPersistence = 0.5;
    _perlinSeed = 0;
}

EditorScene::~EditorScene() {}

void EditorScene::ProcessEvents(App* app, SDL_Event& event) {
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            app->Quit();
        if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            app->Quit();
    }
}

void EditorScene::Update() {
    if (_generatePerlin) {
        if (_perlinTexture != nullptr) {
            Renderer::GetInstance()->DestroyTexture(_perlinTexture);
            _perlinTexture = nullptr;
        }

        _pixels = new double[_perlinWidth*_perlinHeight];
        auto start = std::chrono::high_resolution_clock::now();
        _perlinGen.Generate2D(_pixels, _perlinOctaves, _perlinPersistence);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        std::cout << "Noise values generation: " << duration.count() << "us" << std::endl;
        _generatePerlin = false;

        uint8_t sdlPixels[_perlinWidth*_perlinHeight];
        for (int i = 0; i < _perlinWidth*_perlinHeight; i++)
            sdlPixels[i] = static_cast<uint8_t>(_pixels[i]*255);


        SDL_Surface* surface = Renderer::GetInstance()->CreateSurfaceFrom(
                sdlPixels, _perlinWidth, _perlinHeight, _perlinWidth, SDL_PIXELFORMAT_INDEX8);
        _perlinTexture = Renderer::GetInstance()->CreateTextureFromSurface(surface, 0);
        delete [] _pixels; _pixels = nullptr; // clean the _pixel pointer
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

void EditorScene::MakeImGuiWindow() {
    ImGui::Begin("Perlin Editor");
    if (ImGui::CollapsingHeader("Base parameters")) {
        ImGui::DragInt("Seed", &_perlinSeed, 0.5f, 0, UINT_MAX, "%d", ImGuiSliderFlags_None);
        ImGui::DragInt("Octaves", &_perlinOctaves, 0.5f, 1, 32, "%d", ImGuiSliderFlags_None);
        ImGui::DragFloat("Persistence", &_perlinPersistence, 0.005f, 0.005f, 0.995f,
                "%.3f",ImGuiSliderFlags_None);
        if (ImGui::Button("Generate")) {
            _perlinGen.Seed(_perlinSeed);
            _generatePerlin = true;
        }
    }
    if (ImGui::CollapsingHeader("Coloring")) {
        ImGui::Text("Work in progress...");
        if (ImGui::Button("Color noise")) {}
    }
    if (ImGui::CollapsingHeader("Utilities")) {
        ImGui::Checkbox("Grid", &_showGrid);
    }
    ImGui::End();
}
