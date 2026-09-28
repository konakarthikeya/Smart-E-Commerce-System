#ifndef BST_H
#define BST_H

struct BSTNode
{
    int productId;
    struct BSTNode *left;
    struct BSTNode *right;
};

struct BSTNode* insertBST(struct BSTNode *root, int productId);
struct BSTNode* searchBST(struct BSTNode *root, int productId);
void inorderBST(struct BSTNode *root);
struct BSTNode* deleteBST(struct BSTNode *root, int productId);

#endif
