#ifndef SEARCH_SORT_H
#define SEARCH_SORT_H

#include "structures.h"
#include "bst.h"

void searchProductById(struct Product products[], int productCount);
void searchProductByName(struct Product products[], int productCount);
void searchProductByCategory(struct Product products[], int productCount);
void searchProductByBST(struct Product products[], int productCount, struct BSTNode *root);

void sortByPrice(struct Product products[], int productCount);
void sortByRating(struct Product products[], int productCount);
void sortByName(struct Product products[], int productCount);

#endif