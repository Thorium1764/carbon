#include "cell.h"

Cell InitCell(char chr, uint8_t fcolor, uint8_t bcolor)
{
   Cell cell;
   cell.chr = chr;
   cell.bcolor = bcolor;
   cell.fcolor = fcolor;
   return cell;
}
