#include <stdbool.h>
#include <stdint.h>

#include "cell.h"
#include "framebuffer.h"

bool DrawLine(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Cell cell)
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
}

