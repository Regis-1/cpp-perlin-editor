#include "EditorScene.hpp"
#include "RenderUtils.hpp"

#include <iostream>
#include <chrono>

EditorScene::EditorScene() {
}

EditorScene::~EditorScene() {}

static double MapRange(double value, double fromMin, double fromMax, double toMin, double toMax) {
    // First, normalize the value to a range from 0 to 1 within the original range.
    double normalizedValue = (value - fromMin) / (fromMax - fromMin);
    // Then, scale the normalized value to the new range.
    double mappedValue = normalizedValue * (toMax - toMin) + toMin;
    return mappedValue;
}

void EditorScene::Render() {
    if (_showGrid) {
        RenderUtils::RenderGrid();
    }

    for (int h = 0; h < 600; h++)
        for (int w = 0; w < 600; w++) {
            double color = MapRange(_pixels[h*600+w], 0, 1.0, 0, 255);
            Renderer::GetInstance()->SetColor({(Uint8)color,(Uint8)color,(Uint8)color,255});
            Renderer::GetInstance()->RenderPixel(h, w);
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
    if (_oneGen) {
        _pixels = new double[600*600];
        auto start = std::chrono::high_resolution_clock::now();
        _perlinGen.Generate2D(_pixels, 4, 0.6);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        std::cout << duration.count() << "us" << std::endl;
        std::cout << "-------------------------" << std::endl;
        _oneGen = false;
    }
}
