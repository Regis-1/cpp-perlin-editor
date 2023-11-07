#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include "SDL3/SDL.h"
#include "imgui.h"

static const int NUMBER_OF_PALETTES = 2;

class Renderer {
private:
    Renderer();

    SDL_Renderer* _renderer{nullptr};
    unsigned int _cellSize{16};
    int _scrW, _scrH;
    int _cols, _rows;

    SDL_Palette* _palettes[NUMBER_OF_PALETTES];

    static Renderer* instancePtr;

public:
    Renderer(const Renderer& other) = delete;

    static Renderer* GetInstance() {
        if (instancePtr == nullptr)
            instancePtr = new Renderer();

        return instancePtr;
    }

    const unsigned int GetCellSize() { return _cellSize; }
    std::pair<int, int> GetOutputSize() {
        return {_scrW, _scrH};
    }
    bool IsValid() { return _renderer != nullptr; }

    void SetRenderer(SDL_Renderer* ren);
    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void SetColor(SDL_Color col);
    void SetCellSize(unsigned int size);
    void SetViewport(SDL_Rect viewport);
    void RenderPixel(int x, int y);
    void RenderTile(int x, int y);
    void RenderLine(int x1, int y1, int x2, int y2);
    void RenderTexture(SDL_Texture* texture);
    void Clear() { SDL_RenderClear(_renderer); }
    void DestroyRenderer() { SDL_DestroyRenderer(_renderer); }
    void DestroyTexture(SDL_Texture* texture) { SDL_DestroyTexture(texture); }
    void Present() { SDL_RenderPresent(_renderer); }
    SDL_Surface* CreateSurfaceFrom(void* pixels, int width, int height,
            int pitch, Uint32 format);
    SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface, int paletteIdx);
    void CreateGrayscalePalette();
    void CreateLayeredPalette(std::vector<float> lThres, std::vector<ImVec4> lCols);
};
