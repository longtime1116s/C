#include <stdio.h>

typedef long long   int64;

int64 fib (int64 n)
{
        int64 i;
        int64 num1 = 0, num2 = 1, num3;

        if ( n <= 1 )
            return n;

        for ( i = 0; i < n - 1; i++ )
        {
            num3 = num1 + num2;
            num1 = num2;
            num2 = num3;
        }

        return num3;
}
int main ()
{
        int64 n = 1000000000;

        printf("%lld ¹àÌÜ¤Ï... %lld\n", n, fib(n));
        printf("%lld ¹àÌÜ¤Ï... %lld\n", n, fib(n));
        printf("%lld ¹àÌÜ¤Ï... %lld\n", n, fib(n));
        printf("%lld ¹àÌÜ¤Ï... %lld\n", n, fib(n));
        printf("%lld ¹àÌÜ¤Ï... %lld\n", n, fib(n));

        return 0;
}

