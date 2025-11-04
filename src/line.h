#pragma once
#include "cell.h"
#include <stdint.h>

bool DrawLine(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Cell cell);
bool DrawLineHB(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);
bool DrawVertLine(Cell **framebuffer, uint16_t y, uint16_t x0, uint16_t x1, Cell cell);
bool DrawVertLineHB(Cell **framebuffer, uint16_t y, uint16_t x0, uint16_t x1, uint8_t color);
