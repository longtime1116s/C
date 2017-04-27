#include <stdio.h>

typedef long long   int64;

int64 fibs[1000000001];

int64 fib (int64 n)
{
        if ( n <= 2 )
            fibs[n] = 1;

        if ( fibs[n] != 0 )
            return fibs[n];

        fibs[n] = fib(n - 2) + fib(n - 1);

        return fibs[n];
}

int main ()
{
        int64 n = 12;

        printf("%lld ¹àÌÜ¤Ï... %lld\n", n, fib(n));
        return 0;
}

