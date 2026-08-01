#include <stdio.h>
char *s = "IOTEKKKKK";
int main(void)
{
    printf("s = %p\n",s);
    s[5]='\0';
    printf(s);
    return 0;
}
