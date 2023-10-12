#pragma once

#include "Renderer.hpp"

namespace RenderUtils {
    void RenderGrid() {
        Renderer::GetInstance()->SetColor(0xFF, 0xFF, 0xFF, 0xFF);
        int x1, y1, x2, y2;
        const unsigned int cellSize = Renderer::GetInstance()->GetCellSize();
        std::pair<int, int> scrDims = Renderer::GetInstance()->GetOutputSize();
        int cols = scrDims.first / cellSize;
        int rows = scrDims.second / cellSize;

        for (int i = 0; i < cols; i++) {
            x1 = cellSize * i; y1 = 0;
            x2 = x1; y2 = scrDims.second;
            Renderer::GetInstance()->RenderLine(x1, y1, x2, y2);
        }

        for (int i = 0; i < rows; i++) {
            x1 = 0; y1 = cellSize * i;
            x2 = scrDims.first; y2 = y1;
            Renderer::GetInstance()->RenderLine(x1, y1, x2, y2);
        }
    }
}
