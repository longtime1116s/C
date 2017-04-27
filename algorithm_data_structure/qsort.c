#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH  7

void print_array(
    int     *array,
    int     length)
{
    int     i;
    for ( i = 0; i < length; i++ )
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(
    int     *array,
    int     i,
    int     j)
{
    int     tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

int med3(
    int     a,
    int     b,
    int     c)
{
        if ( a > b )
        {
            if ( c > a )
                return a;
            else if ( b > c )
                return b;
            else
                return c;
        }
        else
        {
            if ( c < a )
                return a;
            else if ( b < c )
                return b;
            else
                return c;
        }
}


void quick_sort_part(
    int    *array,
    int     left,
    int     right)
{
    int     i = left;
    int     j = right;
    int     pivot;

    // 枢軸を決定 (3 つのデータの中央地を取る)
    pivot = med3(array[left], array[(left + right)/2], array[right]);

    /* left が right 以上なら処理終了 */
    if ( left >= right )
        return;

    while ( 1 )
    {
        while ( array[i] > pivot )
            i++;
        while ( array[j] <= pivot )
            j--;

        if ( i >= j )
            break;

        swap(array, i, j);
    }

    /* 枢軸と array[i] を入れ替え */
    swap(array, i, right);

    /* 再帰呼び出し */
    quick_sort_part(array, left, i - 1);
    quick_sort_part(array, j + 1, right);
}


void quick_sort(
    int    *array,
    int     size)
{
    quick_sort_part(array, 0, size-1);
}

int main(void)
{
    int         array[MAX_LENGTH] = {4, 2, 5, 6, 1, 7, 3};
    clock_t     start, end;

    printf("before :");
    print_array(array, MAX_LENGTH);

    start = clock();
    quick_sort(array, MAX_LENGTH);
    end = clock();
    printf("time : %.2f\n", (double)(end-start)/CLOCKS_PER_SEC);

    printf("afger  :");
    print_array(array, MAX_LENGTH);
    return 0;
}
