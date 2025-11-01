#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"
#include "cell.h"
#include "framebuffer.h"

bool InitFrameBuffer(Cell **framebuffer)
{
   size termSize;
   GetTerminalSize(&termSize);
   uint32_t bufferSize = (termSize.columns + 1) * termSize.rows + 1; // + 1 at the end for \0 and at columns for \n
   Cell *tmp = realloc(*framebuffer, bufferSize * sizeof(Cell)); 
   if (!tmp){
      free(*framebuffer);
      return 0;
   }
   *framebuffer = tmp;
   memset(*framebuffer, 20, (bufferSize - 1) * sizeof(Cell));
   (*framebuffer)[bufferSize - 1] = InitCell('\0', 0, 0);
   for (int i = 1; i < termSize.rows; i++){
      (*framebuffer)[(termSize.columns + 1) * i - 1] = InitCell('\n', 0, 0);
   }
   return 1;
}

bool DrawCell(Cell **framebuffer, int x, int y, Cell cell)
{
   size termSize;
   GetTerminalSize(&termSize);
   if (x < 0 || x >= termSize.columns || y < 0 || y >= termSize.rows)
      return 0;
   uint32_t linear_address = y * (termSize.columns + 1) + x;
   (*framebuffer)[linear_address] = cell;
   return 1;
}
