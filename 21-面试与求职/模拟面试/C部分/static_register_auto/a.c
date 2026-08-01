#include <stdio.h>
int a = 0;
void fun_a(void)
{
    printf("Enter %s...................\n",__FUNCTION__);
    a = 10;
    printf("a@fun_a =  %d...................\n",a);
    printf("Exit %s...................\n",__FUNCTION__);
}
