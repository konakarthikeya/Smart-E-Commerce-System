#ifndef SEARCH_SORT_H
#define SEARCH_SORT_H

#include "bst.h"

struct Product
{
    int id;
    char name[50];
    char category[30];
    float price;
    float rating;
    int stock;
};

void searchProductById(struct Product products[], int productCount);
void searchProductByName(struct Product products[], int productCount);
void searchProductByCategory(struct Product products[], int productCount);
void searchProductByBST(struct Product products[], int productCount, struct BSTNode *root);

void sortByPrice(struct Product products[], int productCount);
void sortByRating(struct Product products[], int productCount);
void sortByName(struct Product products[], int productCount);

#endif
