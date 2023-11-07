#include "Renderer.hpp"
#include <algorithm>

Renderer* Renderer::instancePtr = nullptr;

Renderer::Renderer() {
    CreateGrayscalePalette();
}

void Renderer::CreateGrayscalePalette() {
    _palettes[0] = SDL_CreatePalette(256);
    SDL_Color colors[256];
    for (int i = 0; i < 256; i++) {
        colors[i] = {(Uint8)i, (Uint8)i, (Uint8)i, 0xFF};
    }

    if (SDL_SetPaletteColors(_palettes[0], colors, 0, 256) != 0)
        std::cout << "ERROR: " << SDL_GetError() << std::endl;
}

void Renderer::CreateLayeredPalette(std::vector<float> lThres, std::vector<ImVec4> lCols) {
    _palettes[1] = SDL_CreatePalette(256);
    SDL_Color colors[256];

    std::vector<int> indices;
    for (int i = 0; i < lThres.size(); i++)
        indices.push_back(i);

    std::sort(indices.begin(), indices.end(),
            [&lThres](int& i, int& j) {
                return lThres[i] < lThres[j];
            });

    for (auto& lt : lThres)
        lt = (int)(lt * (256 - 1));

    for (auto& col : lCols) {
        col.x *= 255;
        col.y *= 255;
        col.z *= 255;
    }

    int thresMin = 0;
    for (int l = 0; l < indices.size(); l++) {
        int thresMax = lThres[indices[l]];
        for (int i = thresMin; i < thresMax; i++) {
            colors[i].r = lCols[indices[l]].x;
            colors[i].g = lCols[indices[l]].y;
            colors[i].b = lCols[indices[l]].z;
            colors[i].a = 0xFF;
        }
        thresMin = thresMax;
    }

    if (SDL_SetPaletteColors(_palettes[1], colors, 0, 256) != 0)
        std::cout << "ERROR: " << SDL_GetError() << std::endl;
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

void Renderer::SetViewport(SDL_Rect viewport) {
    SDL_SetRenderViewport(_renderer, &viewport);
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
        int paletteIdx) {
    SDL_SetSurfacePalette(surface, _palettes[paletteIdx]);
    SDL_Texture* out = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_DestroySurface(surface); // free surface (we already have a texture)
    return out;
}
