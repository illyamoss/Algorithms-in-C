#include <stdio.h>


void recursion(int n)
{
    if (n == 0)
        return;
    
    recursion(n - 1);
    printf("%d\n", n);
}


int factorial(int n)
{
    if (n == 1)
        return 1;
    return n * factorial(n-1);
}


int main(void)
{
    int f = factorial(5);
    printf("%d\n", f);
    return 0;
}
