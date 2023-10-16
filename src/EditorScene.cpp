#include "EditorScene.hpp"
#include "RenderUtils.hpp"

#include <iostream>
#include <chrono>

EditorScene::EditorScene() {
}

EditorScene::~EditorScene() {}

void EditorScene::Render() {
    if (_showGrid) {
        RenderUtils::RenderGrid();
    }
}

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
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << _perlinGen.OctaveNoise(1.2, 1.4, 0, 3, 0.5) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << duration.count() << "ms" << std::endl;
}
