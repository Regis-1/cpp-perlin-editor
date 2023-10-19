#include "Renderer.hpp"

Renderer* Renderer::instancePtr = nullptr;

Renderer::Renderer() {
    CreatePalettes();
}

void Renderer::CreatePalettes() {
    //grayscale palette
    _palettes[0] = SDL_CreatePalette(256);
    SDL_Color colors[256];
    for (int i = 0; i < 256; i++) {
        colors[i] = {(Uint8)i, (Uint8)i, (Uint8)i, 0xFF};
    }
    SDL_SetPaletteColors(_palettes[0], colors, 0, 256);
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

void Renderer::RenderPixel(int x, int y) {
    SDL_RenderPoint(_renderer, x, y);
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

void Renderer::RenderTexture(SDL_Texture* texture) {
    SDL_RenderTexture(_renderer, texture, NULL, NULL);
}

SDL_Surface* Renderer::CreateSurfaceFrom(void* pixels, int width, int height,
        int pitch, Uint32 format) {

    return SDL_CreateSurfaceFrom(pixels, width, height, pitch, format);
}

SDL_Texture* Renderer::CreateTextureFromSurface(SDL_Surface* surface,
        int palette_idx) {
    SDL_SetSurfacePalette(surface, _palettes[palette_idx]);
    SDL_Texture* out = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_DestroySurface(surface); // free surface (we already have a texture)
    return out;
}
