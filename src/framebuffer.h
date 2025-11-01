#pragma once
#include <stdint.h>
#include "cell.h"

bool InitFrameBuffer(Cell **framebuffer);
bool DrawCell(Cell **framebuffer, int x, int y, Cell cell);
