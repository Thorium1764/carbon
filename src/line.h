#pragma once
#include "cell.h"
#include <stdint.h>

bool DrawLine(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Cell cell);
