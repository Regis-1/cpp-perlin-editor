#include "App.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int, char**) {
    App app("Editor Perlin", SCREEN_WIDTH, SCREEN_HEIGHT);

    if (app.Valid())
        app.Run();

    return 0;
}
