#include <stdbool.h>
#include <stdlib.h>

#include "screen.h"
#include "framebuffer.h"
#include "cell.h"

int main()
{
   Cell *framebuffer = NULL;
   InitScreen();
   if(!InitFrameBuffer(&framebuffer))
      return 1;
   if(!DrawCell(&framebuffer, 0, 0, InitCell('#', 0, 15)))
      return 2;
   DrawFrameBuffer(framebuffer);
   for(;;);
   return 0;
}
