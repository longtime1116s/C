#include <stdio.h>
#include <stdlib.h>


struct Block {
    struct Block    *next;
    int             cells;
};

struct MemManager {
    int             cell_size;
    int             n_cell_per_block;
    int             offset_next;            // cell 内の next への offset
    struct Block    *top;
    void            *free_cells;
};


struct Item {
    struct Item     *next;
    int             id;
};

#define ITEM_PER_BLOCK  (3)

#define get_next_offset(type,next)  (int)&((type *)0)->next

static struct Block*
memtest_alloc_block(
        struct MemManager   *manager,
        int                 size)
{
        struct Block    *block;
        void            *cell;

        /* Block 確保 */
        block = (struct Block*)malloc(sizeof(struct Block));
        if ( block == NULL )
        {
            fprintf(stderr, "fail to malloc block\n");
            goto ERR;
        }
        /* cell 確保 */
        cell = (void *)malloc(size);
        if ( cell == NULL )
        {
            fprintf(stderr, "fail to malloc cell\n");
            goto ERR;
        }
        block->cells = (int)cell;

        if ( manager->top == NULL )
            manager->top = block;

        return block;
ERR:
        if ( block != NULL )
            free(block);
        return NULL;
}

static void
memtest_set_free_cells(
        struct MemManager   *manager,
        struct Block        *block)
{
        int                 cells = block->cells;
        int                 *next;
        int                 i;

        for ( i = 0; i < manager->n_cell_per_block; i++ )
        {
            next = (int *)(cells + manager->offset_next);
            *next = (int)manager->free_cells;
            manager->free_cells = (void *)cells;
            cells += manager->cell_size;
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
            free((int *)block->cells);
            /* Block を解放 */
            free(block);
        }
}

static void *
memtest_alloc_cell(
        struct MemManager   *manager)
{
        struct Block        *top = manager->top;
        struct Block        *block = top;
        void                *ret;
        int                 size;
        int                 *next;

        size = manager->cell_size * manager->n_cell_per_block;

        if ( manager->free_cells == NULL )
        {
            if ( top == NULL )
            {
                printf("-----memtest_alloc_block(first)-----\n");
                block = memtest_alloc_block(manager, size);
            }
            else
            {
                printf("-----memtest_alloc_block(not first)-----\n");
                while( block->next != NULL )
                    block = block->next;
                block->next = memtest_alloc_block(manager, size);
                block = block->next;
            }
            memtest_set_free_cells(manager, block);
        }
        else
            printf("-----free cell still exists-----\n");


        /* 空きの cell を一つ抜いて返す */
        ret = manager->free_cells;
        next = (int *)((int)ret + manager->offset_next);
        manager->free_cells = (void *)*next;
        *next = (int)NULL;

        return ret;
}

static void
memtest_memmanager_item_init(
        struct MemManager   *manager)
{
        manager->cell_size          = sizeof(struct Item);
        manager->n_cell_per_block   = ITEM_PER_BLOCK;
        manager->offset_next        = get_next_offset(struct Item, next);
        manager->top                = NULL;
        manager->free_cells         = NULL;
}

int main(void)
{
        struct MemManager   manager;
        struct Item         *item = NULL;
        int                 i;

        memtest_memmanager_item_init(&manager);
        for ( i = 0; i < 10; i++ )
        {
            printf("-----memtest_alloc_cell  (%d回目)-----\n", i);
            item = (struct Item *)memtest_alloc_cell(&manager);
            printf("  item: %p\n", item);
        }

        memtest_destroy_memmanager(&manager);
        printf("hoge\n");
        return 0;
}
