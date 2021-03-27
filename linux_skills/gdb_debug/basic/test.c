#include <stdio.h>

void func(int *a,int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


int main()
{

    int a = 0;
    int b = 4;

    func(&a,&b);

    return 0;
}
