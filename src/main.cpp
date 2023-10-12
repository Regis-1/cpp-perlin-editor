#include "App.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int, char**) {
    App app("Editor Perlin", SCREEN_WIDTH, SCREEN_HEIGHT);

    if (app.Valid())
        app.Run();

    return 0;
}
