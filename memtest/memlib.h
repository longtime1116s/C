#include <stdio.h>
#include <stdlib.h>

struct Block {
    struct Block    *next;
    char            *cells;
};

struct MemManager {
    int             cell_size;
    int             n_cell_per_block;
    int             offset_next;            // cell 内の next への offset
    struct Block    *top;
    void            *free_cells;
};

void * memtest_alloc_cell(struct MemManager *);
void memtest_destroy_memmanager(struct MemManager *);
void memtest_delete_cell(struct MemManager*, void*);
