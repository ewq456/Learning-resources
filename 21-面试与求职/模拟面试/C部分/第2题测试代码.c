#include <stdio.h>
int i = 0;
 void local_fun(void)
{
    int i = 100;
    printf("i@%s =  %d...................\n",__FUNCTION__,i);
}
int main(void)
{
    printf("i@%s =  %d...................\n",__FUNCTION__,i);
    local_fun();
    printf("i@%s =  %d...................\n",__FUNCTION__,i);
    return 0;
}
