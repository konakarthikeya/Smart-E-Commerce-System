#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct BSTNode* insertBST(struct BSTNode *root, int productId)
{
    if(root == NULL)
    {
        struct BSTNode *newNode;

        newNode = (struct BSTNode *)malloc(sizeof(struct BSTNode));

        newNode->productId = productId;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if(productId < root->productId)
    {
        root->left = insertBST(root->left, productId);
    }
    else if(productId > root->productId)
    {
        root->right = insertBST(root->right, productId);
    }

    return root;
}

struct BSTNode* searchBST(struct BSTNode *root, int productId)
{
    if(root == NULL || root->productId == productId)
    {
        return root;
    }

    if(productId < root->productId)
    {
        return searchBST(root->left, productId);
    }

    return searchBST(root->right, productId);
}

void inorderBST(struct BSTNode *root)
{
    if(root != NULL)
    {
        inorderBST(root->left);

        printf("%d ", root->productId);

        inorderBST(root->right);
    }
}

struct BSTNode* deleteBST(struct BSTNode *root, int productId)
{
    if(root == NULL)
    {
        return root;
    }

    if(productId < root->productId)
    {
        root->left = deleteBST(root->left, productId);
    }
    else if(productId > root->productId)
    {
        root->right = deleteBST(root->right, productId);
    }
    else
    {
        if(root->left == NULL)
        {
            struct BSTNode *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            struct BSTNode *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            struct BSTNode *temp = root->right;

            while(temp->left != NULL)
            {
                temp = temp->left;
            }

            root->productId = temp->productId;

            root->right = deleteBST(root->right, temp->productId);
        }
    }

    return root;
}
