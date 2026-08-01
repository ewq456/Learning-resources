#include <stdio.h>
static int a = 0;
static void fun_a(void)
{
    a = 100;
    printf("a@main =  %d...................\n",a);
}
int main(void)
{
    printf("Entering %s...................\n",__FUNCTION__);
    fun_a();
    printf("Exiting %s...................\n",__FUNCTION__);
    return 0;
}
