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
        BinaryNode  **root)
{
        BinaryNode  **node = root;
        BinaryNode  *new;

        // 挿入すべきところまで移動
        while ( *node != NULL )
        {
            if ( value == (*node)->data->value )
            {
                fprintf(stdout, "the value (%d) already exists\n", value);
                return *node;
            }
            else if ( value < (*node)->data->value )
                node = &(*node)->left;
            else
                node = &(*node)->right;
        }

        new = (BinaryNode *)malloc(sizeof(BinaryNode));
        new->data = (Mydata *)malloc(sizeof(Mydata));
        new->data->value = value;
        new->left = NULL;
        new->right = NULL;
        *node = new;

        return *node;
}

int delete_node(
        int         value,
        BinaryNode  **root)
{
        BinaryNode  **node = root;
        BinaryNode  *del;

        // 削除すべきところまで移動
        while ( *node != NULL )
        {
            if ( value == (*node)->data->value )
                break;

            if ( value < (*node)->data->value )
                node = &(*node)->left;
            else
                node = &(*node)->right;
        }

        if ( *node == NULL )
        {
            fprintf(stdout, "the value (%d) dose not exist\n", value);
            return 1;
        }

        del = *node;

        if ( (*node)->left == NULL && (*node)->right == NULL )
        {   // 子をもたない
            *node = NULL;
            printf("the value (%d) was deleted (no child)\n", value);
        }
        else if ( (*node)->left == NULL )
        {   // 右の子のみ
            *node = del->right;
            printf("the value (%d) was deleted (one child)\n", value);
        }
        else if ( (*node)->right == NULL )
        {   // 左の子のみ
            *node = del->left;
            printf("the value (%d) was deleted (one child)\n", value);
        }
       else
        {   // 左右の子をもつ
            BinaryNode  *replace = del->right;

            // 消すノードの右の子のなかで最小の子を見つける
            while ( replace->left != NULL )
                replace = replace->left;
            *node = replace;
            (*node)->left = del->left;
            printf("the value (%d) was deleted (two child)\n", value);
        }
        free(del->data);
        free(del);

        return 0;
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

void free_node(
        BinaryNode  *node)
{
        if ( node == NULL )
            return;

        // 帰りがけ順でなぞることで、解放する
        free_node(node->left);
        free_node(node->right);
        free(node->data);
        free(node);
}

int main(void)
{
        int         array[MAX_LENGTH] = {4, 2, 5, 6, 1, 7, 3, 5};
        int         i;
        BinaryNode  *node = NULL;

        printf("before :");
        print_array(array, MAX_LENGTH);

        // 二分木作成
        for ( i = 0; i < MAX_LENGTH; i++ )
            insert_node(array[i], &node);

        // 小さい順に出力(5 は重複しているので一度しか登録されない)
        printf("\n----------削除前----------\n");
        print_node(node);
        printf("--------------------------\n");

        // 削除 1/2/5 でそれぞれ違うフローを通る
        delete_node(2, &node);
        delete_node(1, &node);
        delete_node(5, &node);
        delete_node(10, &node);

        printf("\n----------削除後----------\n");
        print_node(node);
        printf("--------------------------\n");

        free_node(node);

        return 0;
}
