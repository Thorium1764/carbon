#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "cell.h"
#include "framebuffer.h"

/*bool DrawLine(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Cell cell)
{
   int dx = x1 - x0;
   int dy = y1 - y0;
   int D = 2*dy - dx;
   int y = y0;
   for (int x = x0; x <= x1; x++){
      if(!DrawCell(framebuffer, x, y, cell))
         return 0;
      if(D > 0){
         y += (dy >= 0) ? 1 : -1;
         D -= 2 * dx;
      }
      D += 2 * dy;
   }
   return 1;
}*/

bool DrawLine(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Cell cell)
{
    int dx = abs((int)x1 - (int)x0);
    int dy = abs((int)y1 - (int)y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        if (!DrawCell(framebuffer, x0, y0, cell))
            return 0;

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    return 1;
}

bool DrawLineHB(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color)
{
    int dx = abs((int)x1 - (int)x0);
    int dy = abs((int)y1 - (int)y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        if (!DrawHalfBlock(framebuffer, x0, y0, color))
            return 0;

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    return 1;
}

bool DrawVertLine(Cell **framebuffer, uint16_t y, uint16_t x0, uint16_t x1, Cell cell)
{
   uint16_t length = x1 - x0;
   length = (length > 0) ? length : -length;
   for(int x = x0; x <= x1; x++){
      if(!DrawCell(framebuffer, x, y, cell))
         return 0;
   }
   return 1;
}

bool DrawVertLineHB(Cell **framebuffer, uint16_t y, uint16_t x0, uint16_t x1, uint8_t color)
{
   uint16_t length = x1 - x0;
   length = (length > 0) ? length : -length;
   for(int x = x0; x <= x1; x++){
      if(!DrawHalfBlock(framebuffer, x, y, color))
         return 0;
   }
   return 1;
}
