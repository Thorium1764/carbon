#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"
#include "sys/ioctl.h"
#include "unistd.h"

#include "screen.h"
#include "cell.h"

void InitScreen()
{
   printf("\x1b[2J");
   printf("\x1b[H");
}

void DrawFrameBuffer(Cell* framebuffer)
{
   printf("\x1b[H");
   for(int i = 0; framebuffer[i].chr; i++){
      printf("\033[38;5;%dm\033[48;5;%dm%c\033[0m", framebuffer[i].fcolor, framebuffer[i].bcolor, framebuffer[i].chr);
   }
}

bool GetTerminalSize(size* w)
{
   struct winsize win;
   if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == -1)
      return false;

   w->columns = win.ws_col;
   w->rows = win.ws_row;

   return true;
}

