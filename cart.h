#ifndef CART_H
#define CART_H

#include <stdbool.h>
#include "models.h"
#include "catalog.h"

typedef struct {
    CartItem *head;
} Cart;

typedef enum {
    CART_REDUCED,        /* some units removed, item stays in the cart */
    CART_REMOVED_ALL,    /* item removed completely                    */
    CART_NOT_IN_CART,
    CART_TOO_MANY        /* asked to remove more than the cart holds   */
} CartResult;

/* ---- data operations (no printing) ---- */
CartItem  *cart_find(const Cart *cart, int product_id);
bool       cart_add(Cart *cart, int product_id, int quantity);  /* merges duplicates */
CartResult cart_reduce(Cart *cart, int product_id, int quantity, int *remaining);
void       cart_clear(Cart *cart);

/* ---- console screen ---- */
void cart_menu(Cart *cart, Catalog *cat);

#endif
