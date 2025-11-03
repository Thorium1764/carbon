#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "screen.h"
#include "framebuffer.h"
#include "cell.h"
#include "line.h"
#include "shape.h"

int main()
{
   Cell *framebuffer = NULL;
   InitScreen();
   if(!InitFrameBuffer(&framebuffer, 0))
      return 1;
   if(!DrawLine(&framebuffer, 30, 30, 60, 10, InitCell("#", 15, 0)))//DrawTriangleWF(&framebuffer, 20, 10, 76, 36, 130, 14, InitCell("#", 15, 0)))
      return 2;
   DrawFrameBuffer(framebuffer);
   for(;;);
   return 0;
}

