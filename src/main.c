#include <stdbool.h>
#include <wchar.h>
#include <stddef.h>
#include <stdio.h>

#include "screen.h"
#include "framebuffer.h"
#include "cell.h"

int main()
{
   Cell *framebuffer = NULL;
   InitScreen();
   if(!InitFrameBuffer(&framebuffer, 0))
      return 1;
   if(!DrawCell(&framebuffer, 22, 25, InitCell("\u2588", 20, 0)))
      return 2;
   if(!DrawCell(&framebuffer, 23, 26, InitCell("\u2588", 15, 0)))
      return 2;
   wprintf(L"%lc", 'a');
   DrawFrameBuffer(framebuffer);
   for(;;);
   return 0;
}

