#ifndef CART_H
#define CART_H

#include "structures.h"

void addToCart(struct CartNode **cart, struct Product products[], int productCount);
void viewCart(struct CartNode *cart);
void removeFromCart(struct CartNode **cart);

#endif