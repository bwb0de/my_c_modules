#include "binary_search_tree.h"
#include "array_tool.h"
#include <stdio.h>
#include <stdlib.h>


bst_t *create_bst(int k){
    bst_node_t *node = malloc(sizeof(bst_node_t));
    node->k = k,
    node->left = NULL,
    node->right = NULL,
    node->parent = NULL,
    node->size = 1;

    bst_t *bst = malloc(sizeof(bst_t));
    bst->root = node;
    bst->size = 1;
    bst->h = 1;

    return bst;
}


void free_bst_node(bst_node_t *node) {
    if (node == NULL) return;
    free_bst_node(node->left);
    free_bst_node(node->right);
    free(node);
}


void free_bst_tree(bst_t *bst) {
    if (bst != NULL) {
        free_bst_node(bst->root);
        free(bst);
    }
}


int bst_min(bst_t *bst){
    bst_node_t *current = bst->root;
    while (1){
        if (current->left != NULL) {
            current = current->left;
            continue;
        }
        return current->k;
    }
}


int bst_max(bst_t *bst){
    bst_node_t *current = bst->root;
    while (1){
        if (current->right != NULL) {
            current = current->right;
            continue;
        }
        return current->k;
    }
}


void bst_in_order_treverse(bst_node_t *node, void *arg2, void (func)(bst_node_t*, void*)) {
    if (node->left != NULL) { bst_in_order_treverse(node->left, arg2, func); }
    if (func != NULL) {
       func(node, arg2);
    }
    if (node->right != NULL) { bst_in_order_treverse(node->right, arg2, func); }
}

void bst_reversed_treverse(bst_node_t *node, void* arg2, void (func)(bst_node_t*, void*)) {
    if (node->right != NULL) { bst_reversed_treverse(node->right, arg2, func); }
    if (func != NULL) {
       func(node, arg2);
    }
    if (node->left != NULL) { bst_reversed_treverse(node->left, arg2, func); }
}



void bst_insert(int k, bst_t *bst){
    bst_node_t *node = malloc(sizeof(bst_node_t));
    node->k = k;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->size = 1;

    bst_node_t *current = bst->root;

    while (1) {
        if (node->k < current->k ) {
            //go left
            if (current->left == NULL) {
                current->left = node;
                node->parent = current;
                bst->size++;
                break;
            } else {
                current = current->left;
                continue;
            }
            
        } else {
            //go right 
            if (current->right == NULL) {
                current->right = node;
                node->parent = current;
                bst->size++;
                break;
            } else {
                current = current->right;
                continue;
            }
        }
    }
}



bst_node_t *bst_search(int k, bst_t *bst){
    bst_node_t *current = bst->root;
    while (1) {
        if (current == NULL) {
            printf("Elemento '%d' não foi encontrado...\n", k);
            return NULL;
        }

        if (current->k == k) {
            return current;
        
        } else {
            if (k < current->k ) {
                current = current->left;
                continue;
            } else {
                current = current->right;
                continue;
            }
        }
    }
}


void bst_delete(int k, bst_t *bst){


}

