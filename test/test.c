#include <locale.h>
#include <stdio.h>

int main()
{
   setlocale(LC_ALL, "");
   printf("\x1b[2J");
   printf("%s", "\u2588");
   return 0;
}
