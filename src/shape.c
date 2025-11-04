#include <stdint.h>
#include <stdbool.h>

#include "cell.h"
#include "framebuffer.h"
#include "line.h"

void swap(uint16_t *x0, uint16_t *y0, uint16_t *x1, uint16_t *y1)
{
   uint16_t tmpx = *x0;
   uint16_t tmpy = *y0;
   *x0 = *x1;
   *y0 = *y1;
   *x1 = tmpx;
   *y1 = tmpy;
}

bool DrawTriangleWF(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Cell cell)
{
   if(!DrawLine(framebuffer, x0, y0, x1, y1, cell))
      return 0;
   if(!DrawLine(framebuffer, x1, y1, x2, y2, cell))
      return 0;
   if(!DrawLine(framebuffer, x2, y2, x0, y0, cell))
      return 0;
   return 1;
}

bool DrawTriangleWFHB(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color)
{
   if(!DrawLineHB(framebuffer, x0, y0, x1, y1, color))
      return 0;
   if(!DrawLineHB(framebuffer, x1, y1, x2, y2, color))
      return 0;
   if(!DrawLineHB(framebuffer, x2, y2, x0, y0, color))
      return 0;
   return 1;
}


bool DrawTriangle(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Cell cell)
{
   if(y0 > y1) swap(&x0, &y0, &x1, &y1);
   if(y1 > y2) swap(&x1, &y1, &x2, &y2);
   if(y0 > y1) swap(&x0, &y0, &x1, &y1);

   int height = y2 - y0;
   if (height == 0)
      return 0;

   for (int y = y0; y <= y2; y++){
      int second_half = y > y1 || y1 == y0;
      int seg_height = second_half ? (y2 - y1) : (y1 - y0);
      if (seg_height == 0) continue;

      float alpha = (float)(y - y0) / height;
      float beta = (float)(y - (second_half ? y1 : y0)) / seg_height;

      uint16_t ax = x0 + (int)((x2 - x0) * alpha);
      uint16_t ay = y0 + (int)((y2 - y0) * alpha);

      uint16_t bx;
      uint16_t by;

      if(second_half){
        bx = x1 + (int)((x2 - x1) * beta);
        by = y1 + (int)((y2 - y1) * beta);
      } else {
        bx = x0 + (int)((x1 - x0) * beta);
        by = y0 + (int)((y1 - y0) * beta);
      }
      if (ax > bx) swap(&ax, &ay, &bx, &by);

      if(!DrawLine(framebuffer, ax, y, bx, y, cell))
         return 0;
   }
   return 1;
}

/*bool DrawTriangleHB(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color)
{
   if(y0 > y1) swap(&x0, &y0, &x1, &y1);
   if(y1 > y2) swap(&x1, &y1, &x2, &y2);
   if(y0 > y1) swap(&x0, &y0, &x1, &y1);

   int height = y2 - y0;
   if (height == 0)
      return 0;

   for (int y = y0; y <= y2; y++){
      int second_half = y > y1 || y1 == y0;
      int seg_height = second_half ? (y2 - y1) : (y1 - y0);
      if (seg_height == 0) continue;

      float alpha = (float)(y - y0) / height;
      float beta = (float)(y - (second_half ? y1 : y0)) / seg_height;

      uint16_t ax = x0 + (int)((x2 - x0) * alpha);
      uint16_t ay = y0 + (int)((y2 - y0) * alpha);

      uint16_t bx;
      uint16_t by;

      if(second_half){
        bx = x1 + (int)((x2 - x1) * beta);
        by = y1 + (int)((y2 - y1) * beta);
      } else {
        bx = x0 + (int)((x1 - x0) * beta);
        by = y0 + (int)((y1 - y0) * beta);
      }
      if (ax > bx) swap(&ax, &ay, &bx, &by);

      if(!DrawLineHB(framebuffer, ax, y, bx, y, color))
         return 0;
   }
   return 1;
}*/


bool DrawTriangleHB(Cell **framebuffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color)
{
    // Helper macro for swapping
    #define SWAP(a,b) do { typeof(a) tmp = a; a = b; b = tmp; } while(0)

    // Sort vertices by ascending Y
    if (y0 > y1) { SWAP(y0, y1); SWAP(x0, x1); }
    if (y1 > y2) { SWAP(y1, y2); SWAP(x1, x2); }
    if (y0 > y1) { SWAP(y0, y1); SWAP(x0, x1); }

    int height = y2 - y0;
    if (height == 0)
        return false;

    for (int y = y0; y <= y2; y++) {
        bool second_half = (y > y1) || (y1 == y0);
        int seg_height = second_half ? (y2 - y1) : (y1 - y0);
        if (seg_height == 0) continue;

        float alpha = (float)(y - y0) / height;
        float beta  = (float)(y - (second_half ? y1 : y0)) / seg_height;

        float axf = x0 + (x2 - x0) * alpha;
        float bxf = second_half ? x1 + (x2 - x1) * beta : x0 + (x1 - x0) * beta;

        uint16_t ax = (uint16_t)axf;
        uint16_t bx = (uint16_t)bxf;
        if (ax > bx) SWAP(ax, bx);

        if (!DrawVertLineHB(framebuffer, y, ax, bx, color))
            return false;
    }

    return true;
}


