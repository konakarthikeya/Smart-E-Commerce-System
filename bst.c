#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/* "slot" is the address of the pointer that leads to a node (the root
   variable itself, or some parent's left/right field).  Walking with slots
   lets insert and remove change the link directly, so no special case is
   needed for the root or for "am I a left or right child". */
static BstNode **find_slot(BstNode **root, int key)
{
    BstNode **slot = root;
    while (*slot != NULL && (*slot)->key != key) {
        slot = (key < (*slot)->key) ? &(*slot)->left : &(*slot)->right;
    }
    return slot;
}

BstNode *bst_insert(BstNode *root, int key)
{
    BstNode **slot = find_slot(&root, key);

    if (*slot == NULL) {
        BstNode *node = malloc(sizeof *node);
        if (node == NULL) {
            return root;                /* out of memory: tree unchanged */
        }
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        *slot = node;
    }
    return root;
}

bool bst_contains(const BstNode *root, int key)
{
    while (root != NULL && root->key != key) {
        root = (key < root->key) ? root->left : root->right;
    }
    return root != NULL;
}

BstNode *bst_remove(BstNode *root, int key)
{
    BstNode **slot = find_slot(&root, key);
    BstNode *victim = *slot;

    if (victim == NULL) {
        return root;
    }

    if (victim->left == NULL) {                 /* 0 or 1 child (right) */
        *slot = victim->right;
    } else if (victim->right == NULL) {         /* 1 child (left)       */
        *slot = victim->left;
    } else {                                    /* 2 children           */
        /* Smallest node of the right subtree takes the victim's place. */
        BstNode **succ_slot = &victim->right;
        while ((*succ_slot)->left != NULL) {
            succ_slot = &(*succ_slot)->left;
        }
        BstNode *succ = *succ_slot;

        *succ_slot = succ->right;               /* unlink successor     */
        succ->left = victim->left;
        succ->right = victim->right;
        *slot = succ;
    }

    free(victim);
    return root;
}

void bst_print_inorder(const BstNode *root)
{
    if (root == NULL) {
        return;
    }
    bst_print_inorder(root->left);
    printf("%d ", root->key);
    bst_print_inorder(root->right);
}

void bst_destroy(BstNode *root)
{
    if (root == NULL) {
        return;
    }
    bst_destroy(root->left);
    bst_destroy(root->right);
    free(root);
}
