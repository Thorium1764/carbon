#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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
   if(!DrawTriangleWFHB(&framebuffer, 40, 14, 70, 40, 10, 40, 15))
      return 2;
   DrawFrameBuffer(framebuffer);
   free(framebuffer);
   for(;;);
   return 0;
}

