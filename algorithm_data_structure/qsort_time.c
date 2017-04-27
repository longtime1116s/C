#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_LENGTH  10000

void print_array(
    unsigned int    *array,
    int             length)
{
    int     i;
    for ( i = 0; i < length; i++ )
    {
        printf("%u ", array[i]);
    }
    printf("\n");
}

void swap(
    unsigned int    *array,
    int             i,
    int             j)
{
    unsigned int    tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

int med3(
    unsigned int    a,
    unsigned int    b,
    unsigned int    c)
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
    unsigned int    *array,
    int             left,
    int             right)
{
    int             i = left;
    int             j = right;
    unsigned int    pivot;

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
    unsigned int    *array,
    int             size)
{
    quick_sort_part(array, 0, size-1);
}

clock_t times_clock()
{
        struct tms t;
        return times(&t);
}

int main(void)
{
    unsigned int    array[MAX_LENGTH];
    int             i;
    clock_t         start, end;

    // 乱数作成
    srand((unsigned int)time(NULL));
    for ( i = 0; i < MAX_LENGTH; i++ )
        array[i] = rand();
    printf("before :");
    print_array(array, MAX_LENGTH);

    start = times_clock();
    quick_sort(array, MAX_LENGTH);
    end = times_clock();

    printf("start time(ms) : %.2f\n", (double)start);
    printf("end   time(ms) : %.2f\n", (double)(end));
    printf("time(ms)       : %.2f\n", (double)(end-start));

//     printf("after  :");
//     print_array(array, MAX_LENGTH);
    return 0;
}
