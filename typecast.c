#include <stdio.h>


int main(void)
{
    int a = 45;
    int b = 2;

    float r = (float)a / b;

    printf("%f\n", r);

    int a1 = 5;
    float b2 = 6.2;
    float result = a1 + b2;

    printf("%f\n", result);

    void *ptr;
    int *intPtr = (int *)ptr;

    float f = 5.5;
    int i = (int)f; // casting flaot to int, resulting in i = 5

    // casting to a larger type
    int small = 10;
    long large = (long)small; // Casting int to long, no data loss expected

    // casting to a smaller type
    long largeValue = 12345678919;
    short smallValue = (short)largeValue; // potential data loss

    printf("Short: %hd\n", smallValue);

    return 0;
}
