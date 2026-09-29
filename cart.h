#ifndef CART_H
#define CART_H

struct CartNode
{
    int productId;
    struct CartNode *next;
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

void addToCart(struct CartNode **cart, struct Product products[], int productCount);
void viewCart(struct CartNode *cart);
void removeFromCart(struct CartNode **cart);

#endif
