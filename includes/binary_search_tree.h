#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "array_tool.h"
typedef struct bst_node_t bst_node_t;

struct bst_node_t {
    int k;
    bst_node_t *left;
    bst_node_t *right;
    bst_node_t *parent;
    int size;
};

typedef struct {
    bst_node_t *root;
    int size;
    int h;
} bst_t;


bst_t *create_bst(int k);
void free_bst_node(bst_node_t *node);
void free_bst_tree(bst_t *bst);
void bst_insert(int k, bst_t *bst);
bst_node_t *bst_search(int k, bst_t *bst);
void bst_delete(int k, bst_t *bst);

int bst_min(bst_t *bst);
int bst_max(bst_t *bst);

void bst_in_order_treverse(bst_node_t *node, void* arg2, void (func)(bst_node_t*, void*));
void bst_reversed_treverse(bst_node_t *node, void* arg2, void (func)(bst_node_t*, void*));



#endif

