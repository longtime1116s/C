#include <stdio.h>

typedef long long   int64;

int64 fib (int64 n)
{
        // 0, 1 項目はそれぞれ 0, 1
        if ( n <= 1 )
            return n;

        return fib(n-1) + fib(n-2);
}

int main ()
{
        int64 n = 12;

        printf("%lld 項目は... %lld\n", n, fib(n));

        return 0;
}

