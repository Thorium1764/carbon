#include <stdbool.h>
#include <stdlib.h>

#include "screen.h"
#include "framebuffer.h"
#include "cell.h"

int main()
{
   Cell *framebuffer = NULL;
   InitScreen();
   if(!InitFrameBuffer(&framebuffer, 0))
      return 1;
   if(!DrawCell(&framebuffer, 23, 26, InitCell('#', 15, 0)))
      return 2;
   if(!DrawCell(&framebuffer, 23, 27, InitCell('#', 15, 0)))
      return 2;
   DrawFrameBuffer(framebuffer);
   for(;;);
   return 0;
}

