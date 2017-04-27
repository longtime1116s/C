#include <stdio.h>

#define TABLE_SIZE  (8)
#define QUEEN_NUM   (8)

int     table[TABLE_SIZE][TABLE_SIZE];
int     solution_num = 1;

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

        printf("solution : %d\n", solution_num);
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
        printf("\n");

        solution_num++;
}

void put_queen(
        int     x,
        int     y)
{
        int     i, j;

        // �Ԥ�����
        for ( j = 0; j < TABLE_SIZE; j++ )
            table[x][j]++;

        // �������
        for ( i = 0; i < TABLE_SIZE; i++ )
            table[i][y]++;

        // �Ф������
        for ( i = x, j = y; i >= 0 && j < TABLE_SIZE; i--, j++ )
            table[i][j]++;
        for ( i = x, j = y; i >= 0 && j >= 0; i--, j-- )
            table[i][j]++;
        for ( i = x, j = y; i < TABLE_SIZE && j < TABLE_SIZE; i++, j++ )
            table[i][j]++;
        for ( i = x, j = y; i < TABLE_SIZE && j >= 0; i++, j-- )
            table[i][j]++;

        // queen ���֤�
        table[x][y] = QUEEN;

        return;
}
void remove_queen(
        int     x,
        int     y)
{
        int     i, j;

        // ��
        for ( j = 0; j < TABLE_SIZE; j++ )
            table[x][j]--;

        // ��
        for ( i = 0; i < TABLE_SIZE; i++ )
            table[i][y]--;

        // �Ф�
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

void try(
        int     x,              // ���ιԤ���õ����Ϥ����
        int     queen_count)    // ��������θ��ߤο�
{
        int     i, j;

        if ( queen_count == QUEEN_NUM )
            print_queens();

        for ( i = x; i < TABLE_SIZE; i++ )
        {
            for ( j = 0; j < TABLE_SIZE; j++ )
            {
                if ( table[i][j] == FREE )
                {
                    put_queen(i, j);
                    try(i + 1, queen_count + 1);
                    remove_queen(i, j);
                }
            }
        }
}

int main (void)
{
        try(0, 0);

        return 0;
}
