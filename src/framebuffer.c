#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>
#include <stddef.h>

#include "screen.h"
#include "cell.h"
#include "framebuffer.h"

bool InitFrameBuffer(Cell **framebuffer, uint8_t bg_color)
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
   for (int i = 0; i < bufferSize; i++){
      (*framebuffer)[i].chr = " ";
      (*framebuffer)[i].bcolor = bg_color;
      (*framebuffer)[i].fcolor = bg_color;
   }
   (*framebuffer)[bufferSize - 1] = InitCell("\0", 0, 0);
   for (int i = 1; i < termSize.rows - 1; i++){
      (*framebuffer)[(termSize.columns + 1) * i - 1] = InitCell("\n", 0, 0);
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

bool DrawHalfBlock(Cell **framebuffer, uint16_t x, uint16_t y, uint8_t color)
{
   size termSize;
   GetTerminalSize(&termSize);
   if (x < 0 || x >= termSize.columns || y < 0 || y >= 2 * termSize.rows)
      return 0;
   if(y % 2 == 1){
      uint32_t linear_address = ((y - 1) / 2) * (termSize.columns + 1) + x;
      (*framebuffer)[linear_address].bcolor = color;
   } else if (y % 2 == 0) {
      uint32_t linear_address = (y / 2) * (termSize.columns + 1) + x;
      (*framebuffer)[linear_address].fcolor = color;
      (*framebuffer)[linear_address].chr = "\u2580";
   }
   return 1;
}
