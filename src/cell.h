#pragma once
#include <stdint.h>
#include <wchar.h>
#include <stddef.h>

typedef struct {
   char *chr;
   uint8_t fcolor;
   uint8_t bcolor;
} Cell;

Cell InitCell(char *chr, uint8_t fcolor, uint8_t bcolor);
