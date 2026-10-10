#ifndef ORDERS_H
#define ORDERS_H

#include "models.h"
#include "cart.h"
#include "catalog.h"

/* Completed purchases, oldest first. */
typedef struct {
    Receipt *head;
    Receipt *tail;
} History;

void history_destroy(History *history);

/* Checkout: validate stock, show the bill, ask to pay, then update stock,
   record the purchase and empty the cart. */
void orders_checkout(Cart *cart, History *history, Catalog *cat);

/* Sub-menu: display / search the purchase history. */
void history_menu(const History *history, Catalog *cat);

#endif
