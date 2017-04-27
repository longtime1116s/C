#include <stdio.h>
#include <stdlib.h>


#define ITEM_PER_BLOCK  (3)

struct Item {
    struct Item     *next;
    int             id;
};

struct Block {
    struct Block    *next;
    struct Item     *items;
};

struct MemManager {
    int             n_item_per_block;
    struct Block    *top;
};

static struct Block*
memtest_alloc_block(
        struct MemManager *manager)
{
        struct Block    *block;
        struct Item     *item;

        /* Block 確保 */
        block = (struct Block*)malloc(sizeof(struct Block));
        if ( block == NULL )
        {
            fprintf(stderr, "fail to malloc block\n");
            goto ERR;
        }
        /* item 確保 */
        item = (struct Item*)malloc(sizeof(struct Item)*manager->n_item_per_block);
        if ( item == NULL )
        {
            fprintf(stderr, "fail to malloc item\n");
            goto ERR;
        }
        block->items = item;

        if ( manager->top == NULL )
            manager->top = block;

        return block;
ERR:
        if ( block != NULL )
            free(block);
        return NULL;
}

static void
memtest_set_free_items(
        struct MemManager   *manager,
        struct Block        *block,
        struct Item         **free_items)
{
        struct Item         *item = block->items;
        int                 i;

        for ( i = 0; i < manager->n_item_per_block; i++ )
        {
            item->next = *free_items;
            *free_items = item;
            item++;
        }
}
static void
memtest_destroy_memmanager(
        struct MemManager *manager)
{
        struct Block    *block, *next;

        for ( block = manager->top; block != NULL; block = next )
        {
            next = block->next;
            /* Item を解放 */
            free(block->items);
            block->items = NULL;
            /* Block を解放 */
            free(block);
            block = NULL;
        }
}

static struct Item *
memtest_alloc_item(
        struct MemManager   *manager,
        struct Item         **free_items)
{
        struct Block        *top = manager->top;
        struct Block        *block = top;
        struct Item         *ret;

        if ( *free_items == NULL )
        {
            if ( top == NULL )
            {
                printf("-----memtest_alloc_block(first)-----\n");
                block = memtest_alloc_block(manager);
            }
            else
            {
                printf("-----memtest_alloc_block(not first)-----\n");
                while( block->next != NULL )
                    block = block->next;
                block->next = memtest_alloc_block(manager);
                block = block->next;
            }
            memtest_set_free_items(manager, block, free_items);
        }
        else
            printf("-----free item still exists-----\n");


        /* 空きの item を一つ抜いて返す */
        ret = *free_items;
        *free_items = (*free_items)->next;
        ret->next = NULL;

        return ret;
}

int main(void)
{
        struct MemManager   manager={ITEM_PER_BLOCK, NULL};
        struct Item         *free_items = NULL;
        struct Item         *item = NULL;
        int                 i;

        for ( i = 0; i < 10; i++ )
        {
            printf("-----memtest_alloc_item  (%d回目)-----\n", i);
            item = memtest_alloc_item(&manager, &free_items);
            printf("  item: %p\n", item);
        }

        memtest_destroy_memmanager(&manager);
        printf("hoge\n");
        return 0;
}
