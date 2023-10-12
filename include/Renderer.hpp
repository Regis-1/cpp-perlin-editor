#pragma once

#include <iostream>
#include <utility>
#include "SDL3/SDL.h"

class Renderer {
private:
    Renderer();

    SDL_Renderer* _renderer{nullptr};
    unsigned int _cellSize{16};
    int _scrW, _scrH;
    int _cols, _rows;

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
    void RenderTile(int x, int y);
    void RenderLine(int x1, int y1, int x2, int y2);
    void Clear() { SDL_RenderClear(_renderer); }
    void DestroyRenderer() { SDL_DestroyRenderer(_renderer); }
    void Present() { SDL_RenderPresent(_renderer); }
};
