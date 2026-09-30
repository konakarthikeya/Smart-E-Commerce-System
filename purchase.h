#ifndef PURCHASE_H
#define PURCHASE_H

#include "cart.h"

struct PurchaseNode
{
    int productId;
    struct PurchaseNode *next;
};

void purchaseProducts(struct CartNode **cart,
                      struct PurchaseNode **purchaseHistory,
                      struct Product products[],
                      int productCount);

void displayPurchaseHistory(struct PurchaseNode *purchaseHistory,
                            struct Product products[],
                            int productCount);

void searchPurchaseHistory(struct PurchaseNode *purchaseHistory,
                           struct Product products[],
                           int productCount);

#endif
