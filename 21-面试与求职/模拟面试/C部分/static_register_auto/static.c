#include <stdio.h>

void add_static_val(int arg)
{
   register static int sta_val = 0;
   if(arg==1)
   {
     sta_val += 10;
   }
   if(sta_val==100)
   {
      puts("work end...");
   }
}
int main(void)
{
  int i;
  
  for(i=0;i<10;i++){
     add_static_val(1);
  }
  return 0;
}
