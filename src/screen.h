#pragma once
#include "stdint.h"
#include "cell.h"

typedef struct {
   uint16_t columns;
   uint16_t rows;
} size;

void InitScreen();
void DrawFrameBuffer(Cell *framebuffer);
bool GetTerminalSize(size* win);
