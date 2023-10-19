#include "App.hpp"

App::App(std::string title, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD) != 0) {
        std::cout << "Error: SDL_Init(): " << SDL_GetError() << std::endl;
        _valid = false;
        return;
    }

    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    SDL_WindowFlags win_flags = (SDL_WindowFlags)(
            SDL_WINDOW_OPENGL
            );

    _window = SDL_CreateWindow(title.c_str(), w, h, win_flags);
    if (_window == nullptr) {
        std::cout << "Error: SDL_CreateWindow(): " << SDL_GetError() << std::endl;
        _valid = false;
        return;
    }

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(_window, NULL,
            SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Error: SDL_CreateRenderer(): " << SDL_GetError() << std::endl;
        _valid = false;
        return;
    }

    SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForSDLRenderer(_window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // other stuff
    Renderer::GetInstance()->SetRenderer(renderer);
    _sceneStack.push_back(new EditorScene);
}

App::~App() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    Renderer::GetInstance()->DestroyRenderer();
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void App::Run() {
    while(!_shouldQuit) {
        // events
        _sceneStack.back()->ProcessEvents(this, _event);

        // update
        _sceneStack.back()->Update();

        // render
        Renderer::GetInstance()->SetColor(0,0,0,255);
        Renderer::GetInstance()->Clear();

        _sceneStack.back()->Render();

        Renderer::GetInstance()->Present();
    }
}
