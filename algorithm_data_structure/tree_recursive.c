#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH  8

typedef struct Mydata
{
        int                 value;
} Mydata;

typedef struct BinaryNode
{
        struct BinaryNode   *left;
        struct BinaryNode   *right;
        Mydata              *data;
} BinaryNode;


void print_array(
        int     *array,
        int     length)
{
        int     i;
        for ( i = 0; i < length; i++ )
            printf("%d ", array[i]);
        printf("\n");
}

BinaryNode* insert_node(
        int         value,
        BinaryNode  **node)
{
        if ( *node == NULL )
            *node = (BinaryNode *)calloc(1, sizeof(BinaryNode));

        if ( (*node)->data == NULL )
        {
            (*node)->data = (Mydata *)malloc(sizeof(Mydata));
            (*node)->data->value = value;
            return *node;
        }

        if ( (*node)->data->value == value )
        {
            fprintf(stdout, "the value (%d) already exists\n", value);
            return *node;
        }
        else if ( (*node)->data->value > value )
            return insert_node(value, &(*node)->left);
        else
            return insert_node(value, &(*node)->right);
}

void print_node(
        BinaryNode  *node)
{
        if ( node == NULL )
            return;

        // 通りがけ順でなぞることで、ソートして表示する
        print_node(node->left);
        printf("value : %d\n", node->data->value);
        print_node(node->right);
        return;
}

int main(void)
{
        int         array[MAX_LENGTH] = {4, 2, 5, 6, 1, 7, 3, 5};
        int         i;
        BinaryNode  *node = NULL;

        printf("before :");
        print_array(array, MAX_LENGTH);

        for ( i = 0; i < MAX_LENGTH; i++ )
            insert_node(array[i], &node);

        // 小さい順に出力(5 は重複しているので一度しか登録されない)
        print_node(node);

        return 0;
}
