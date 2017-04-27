#include <stdio.h>

typedef long long   int64;

void multiple(
        int64   mat[4],     // [i]
        int64   result[4])  // [u] mat * result の結果を入れる
{
        int64   tmp[4];
        int64   i;

        tmp[0] = mat[0] * result[0] + mat[1] * result[2];
        tmp[1] = mat[0] * result[1] + mat[1] * result[3];
        tmp[2] = mat[2] * result[0] + mat[3] * result[2];
        tmp[3] = mat[2] * result[1] + mat[3] * result[3];

        for ( i = 0; i < 4; i++ )
            result[i] = tmp[i];
}

int64 fib (
        int64   n)
{
        if ( n <= 1 )
            return n;

        int64 mat[4] = {1, 1, 1, 0};
        int64 result[4] = {1, 0, 0, 1};

        while ( n > 0 )
        {
            printf(" n      : %lld\n", n);
            printf(" mat    : {%lld, %lld, %lld, %lld}\n", mat[0], mat[1], mat[2], mat[3]);
            if ( n % 2 == 1 )
            {
                multiple(mat, result);
                printf(" result : {%lld, %lld, %lld, %lld}\n", result[0], result[1], result[2], result[3]);
            }
            else
                printf("(result : {%lld, %lld, %lld, %lld})\n", result[0], result[1], result[2], result[3]);

            multiple(mat, mat);
            n /= 2;
        }

        return result[2];
}
int main ()
{
        int64 n = 1000000000;

        n = 21;
        printf("%lld 項目は... %lld\n", n, fib(n));

        return 0;
}

