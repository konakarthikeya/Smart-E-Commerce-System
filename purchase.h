#ifndef PURCHASE_H
#define PURCHASE_H

#include "structures.h"

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