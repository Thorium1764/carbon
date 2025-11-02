#pragma once
#include <stdint.h>
#include "cell.h"

bool InitFrameBuffer(Cell **framebuffer, uint8_t bg_color);
bool DrawCell(Cell **framebuffer, int x, int y, Cell cell);
