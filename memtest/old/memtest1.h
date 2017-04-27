struct Block {
    struct Block    *next;
    struct Item     *items;
};

struct MemManager {
    int             n_item_per_block;
    struct Block    *top;
};
