#include <stdint.h>
#include <stdbool.h>

#include "cell.h"
#include "framebuffer.h"
#include "line.h"

bool DrawTriangleWF(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Cell cell)
{
   if(!DrawLine(framebuffer, x0, y0, x1, y1, cell))
      return 0;
   if(!DrawLine(framebuffer, x1, y1, x2, y2, cell))
      return 0;
   /*if(!DrawLine(framebuffer, x2, y2, x0, y0, cell))
      return 0;*/
   return 1;
}
