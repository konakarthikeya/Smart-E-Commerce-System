#ifndef BST_H
#define BST_H

#include <stdbool.h>

/* Binary search tree that indexes product IDs. */
typedef struct BstNode {
    int key;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

BstNode *bst_insert(BstNode *root, int key);   /* ignores duplicates      */
bool     bst_contains(const BstNode *root, int key);
BstNode *bst_remove(BstNode *root, int key);   /* no-op if key is missing */
void     bst_print_inorder(const BstNode *root);
void     bst_destroy(BstNode *root);

#endif
