#ifndef PURCHASE_H
#define PURCHASE_H

struct PurchaseNode
{
    int productId;
    struct PurchaseNode *next;
};

struct Product
{
    int id;
    char name[50];
    char category[30];
    float price;
    float rating;
    int stock;
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
