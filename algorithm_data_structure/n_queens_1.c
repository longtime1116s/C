#include <stdio.h>

#define TABLE_SIZE  (8)
#define QUEEN_NUM   (8)

int     table[TABLE_SIZE][TABLE_SIZE];

typedef enum {
        QUEEN= -1,
        FREE
} TABLE_STATUS;

typedef enum {
        TRUE = 0,
        FALSE,
        SUCCESS = 0,
        FAIL
} BOOL;

void print_queens (void)
{
        int     i, j;
        for ( i = 0; i < TABLE_SIZE; i++ )
        {
            for ( j = 0; j < TABLE_SIZE; j++ )
            {
                if ( table[i][j] == QUEEN )
                    printf("Q ");
                else
                    printf(". ");
            }
            printf("\n");
        }
}

void put_queen(
        int     x,
        int     y)
{
        int     i, j;

        // 行を埋める
        for ( j = 0; j < TABLE_SIZE; j++ )
            table[x][j]++;

        // 列を埋める
        for ( i = 0; i < TABLE_SIZE; i++ )
            table[i][y]++;

        // 斜めを埋める
        for ( i = x, j = y; i >= 0 && j < TABLE_SIZE; i--, j++ )
            table[i][j]++;
        for ( i = x, j = y; i >= 0 && j >= 0; i--, j-- )
            table[i][j]++;
        for ( i = x, j = y; i < TABLE_SIZE && j < TABLE_SIZE; i++, j++ )
            table[i][j]++;
        for ( i = x, j = y; i < TABLE_SIZE && j >= 0; i++, j-- )
            table[i][j]++;

        // queen を置く
        table[x][y] = QUEEN;

        return;
}
void remove_queen(
        int     x,
        int     y)
{
        int     i, j;

        // 行
        for ( j = 0; j < TABLE_SIZE; j++ )
            table[x][j]--;

        // 列
        for ( i = 0; i < TABLE_SIZE; i++ )
            table[i][y]--;

        // 斜め
        for ( i = x, j = y; i >= 0 && j < TABLE_SIZE; i--, j++ )
            table[i][j]--;
        for ( i = x, j = y; i >= 0 && j >= 0; i--, j-- )
            table[i][j]--;
        for ( i = x, j = y; i < TABLE_SIZE && j < TABLE_SIZE; i++, j++ )
            table[i][j]--;
        for ( i = x, j = y; i < TABLE_SIZE && j >= 0; i++, j-- )
            table[i][j]--;

        // queen
        table[x][y] = FREE;

        return;
}

BOOL try(
        int     queen_count)
{
        int     i, j;

        if ( queen_count >= QUEEN_NUM )
            return SUCCESS;

        for ( i = 0; i < TABLE_SIZE;i++ )
        {
            for ( j= 0;j< TABLE_SIZE;j++ )
            {
                if ( table[i][j] == FREE )
                {
                    put_queen(i, j);
                    if ( try(queen_count + 1) == SUCCESS )
                        return SUCCESS;
                    remove_queen(i, j);
                }
            }
        }

        return FAIL;
}

int main (void)
{
        if ( try(0) == SUCCESS )
            print_queens();
        else
            printf("no solution for %d queens\n", QUEEN_NUM);

        return 0;
}
