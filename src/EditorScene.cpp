#include "EditorScene.hpp"
#include "RenderUtils.hpp"

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

void EditorScene::Update() {}
