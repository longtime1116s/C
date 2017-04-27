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

        // �������٤��Ȥ���ޤǰ�ư
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

        // ������٤��Ȥ���ޤǰ�ư
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
        {   // �Ҥ�⤿�ʤ�
            *node = NULL;
            printf("the value (%d) was deleted (no child)\n", value);
        }
        else if ( (*node)->left == NULL )
        {   // ���λҤΤ�
            *node = del->right;
            printf("the value (%d) was deleted (one child)\n", value);
        }
        else if ( (*node)->right == NULL )
        {   // ���λҤΤ�
            *node = del->left;
            printf("the value (%d) was deleted (one child)\n", value);
        }
       else
        {   // �����λҤ���
            BinaryNode  *replace = del->right;

            // �ä��Ρ��ɤα��λҤΤʤ��ǺǾ��λҤ򸫤Ĥ���
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

        // �̤꤬����Ǥʤ��뤳�Ȥǡ������Ȥ���ɽ������
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

        // ���꤬����Ǥʤ��뤳�Ȥǡ���������
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

        // ��ʬ�ں���
        for ( i = 0; i < MAX_LENGTH; i++ )
            insert_node(array[i], &node);

        // ��������˽���(5 �Ͻ�ʣ���Ƥ���Τǰ��٤�����Ͽ����ʤ�)
        printf("\n----------�����----------\n");
        print_node(node);
        printf("--------------------------\n");

        // ��� 1/2/5 �Ǥ��줾��㤦�ե����̤�
        delete_node(2, &node);
        delete_node(1, &node);
        delete_node(5, &node);
        delete_node(10, &node);

        printf("\n----------�����----------\n");
        print_node(node);
        printf("--------------------------\n");

        free_node(node);

        return 0;
}
