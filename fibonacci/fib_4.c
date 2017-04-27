#include <stdio.h>

typedef long long   int64;

void multiple(
        int64   result[4],
        int64   mat[4])
{
        int64   tmp[4];
        int64   i;

        tmp[0] = result[0] * mat[0] + result[1] * mat[2];
        tmp[1] = result[0] * mat[1] + result[1] * mat[3];
        tmp[2] = result[2] * mat[0] + result[3] * mat[2];
        tmp[3] = result[2] * mat[1] + result[3] * mat[3];

        for ( i = 0; i < 4; i++ )
            result[i] = tmp[i];
}

int64 fib (
        int64   n)
{
        if ( n <= 1 )
            return n;

        int64 result[4] = {1, 1, 1, 0};
        int64 mat[4] = {1, 1, 1, 0};

        while ( n > 0 )
        {
            if ( n == 1 )
                return result[2];

            multiple(result, mat);
            n--;
        }

        return result[2];
}
int main ()
{
        int64 n = 1000000000;

        printf("%lld π‡Ã‹§œ... %lld\n", n, fib(n));

        return 0;
}

