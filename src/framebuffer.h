#pragma once
#include <stdint.h>
#include "cell.h"

bool InitFrameBuffer(Cell **framebuffer, uint8_t bg_color);
bool DrawCell(Cell **framebuffer, int x, int y, Cell cell);
bool DrawHalfBlock(Cell **framebuffer, uint16_t x, uint16_t y, uint8_t color);
