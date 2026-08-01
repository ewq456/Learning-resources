#include <stdio.h>

int main(void)
{
   register float a = 0;
   float i = 100;
   while(i)
   {
        a += i--;
   }
   printf("\na = %f\n",a);
   return 0;
}
