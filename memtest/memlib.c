#include <stdio.h>
#include <stdlib.h>
#include "memlib.h"

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
        block->cells = (char *)cell;
        block->next = NULL;

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
        char                *cells = block->cells;
        char                **next;
        int                 i;

        for ( i = 0; i < manager->n_cell_per_block; i++ )
        {
            next = (char **)(cells + manager->offset_next);
            *next = manager->free_cells;
            manager->free_cells = (void *)cells;
            cells += manager->cell_size;
        }
}
void
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

void *
memtest_alloc_cell(
        struct MemManager   *manager)
{
        struct Block        *top = manager->top;
        struct Block        *block = top;
        void                *ret;
        int                 size;
        char                **next;

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
        next = ret + manager->offset_next;
        manager->free_cells = (void *)*next;
        *next = (char *)NULL;

        return ret;
}
void
memtest_delete_cell(
        struct MemManager   *manager,
        void                *cell)
{
        char                **next;

        next = (char **)(cell + manager->offset_next);
        *next = manager->free_cells;
        manager->free_cells = cell;
}
