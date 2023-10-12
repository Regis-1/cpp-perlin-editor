#include "Renderer.hpp"

Renderer* Renderer::instancePtr = nullptr;

Renderer::Renderer() {
}

void Renderer::SetRenderer(SDL_Renderer* ren) {
    _renderer = ren;
    SDL_GetCurrentRenderOutputSize(_renderer, &_scrW, &_scrH);
    _cols = _scrW / _cellSize;
    _rows = _scrH / _cellSize;
}

void Renderer::SetCellSize(unsigned int size) {
    _cellSize = size;
}

void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void Renderer::SetColor(SDL_Color col) {
    SDL_SetRenderDrawColor(_renderer, col.r, col.g, col.b, col.a);
}

void Renderer::RenderLine(int x1, int y1, int x2, int y2) {
    SDL_RenderLine(_renderer, x1, y1, x2, y2);
}

void Renderer::RenderTile(int x, int y) {
    SDL_FRect rect = {
        (float)(_cellSize * (_cols / 2) + (_cellSize * x)),
        (float)(_cellSize * (_rows / 2) - (_cellSize * y)),
        (float)_cellSize, (float)_cellSize
    };
    SDL_RenderFillRect(_renderer, &rect);
}
