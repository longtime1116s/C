#include <stdio.h>
#include <stdlib.h>
#include "memlib.h"

#define ITEM_PER_BLOCK              (3)
#define get_next_offset(type,next)  (int)&((type *)0)->next

struct Item {
    struct Item     *next;
    int             id;
};

static struct Item *
memtest_alloc_item(
        struct MemManager   *manager)
{
        return (struct Item *)memtest_alloc_cell(manager);

}
static void
memtest_delete_item(
        struct MemManager   *manager,
        struct Item         *item)
{
        memtest_delete_cell(manager, (void *)item);
}

int main(void)
{
        struct MemManager   manager = {sizeof(struct Item),
                                       ITEM_PER_BLOCK,
                                       get_next_offset(struct Item, next),
                                       NULL,
                                       NULL};
        struct Item         *items[20];
        int                 i;

        for ( i = 0; i < 10; i++ )
        {
            printf("-----memtest_alloc_item  (%d回目)-----\n", i+1);
            items[i] = memtest_alloc_item(&manager);
            printf("  item: %p\n", items[i]);
        }
        for ( i = 0; i < 10; i+=2 )
        {
            printf("-----memtest_delete_item  (%d個目)-----\n", i+1);
            printf("  item: %p\n", items[i]);
            memtest_delete_item(&manager, items[i]);
        }
        for ( i = 10; i < 20; i++ )
        {
            printf("-----memtest_alloc_item  (%d回目)-----\n", i+1);
            items[i] = memtest_alloc_item(&manager);
            printf("  item: %p\n", items[i]);
        }

        memtest_destroy_memmanager(&manager);
        return 0;
}
