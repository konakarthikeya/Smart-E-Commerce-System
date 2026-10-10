#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "cart.h"
#include "console.h"

/* ------------------------- data operations ------------------------- */

CartItem *cart_find(const Cart *cart, int product_id)
{
    for (CartItem *it = cart->head; it != NULL; it = it->next) {
        if (it->product_id == product_id) {
            return it;
        }
    }
    return NULL;
}

bool cart_add(Cart *cart, int product_id, int quantity)
{
    CartItem *existing = cart_find(cart, product_id);
    if (existing != NULL) {
        existing->quantity += quantity;
        return true;
    }

    CartItem *node = malloc(sizeof *node);
    if (node == NULL) {
        return false;
    }
    node->product_id = product_id;
    node->quantity = quantity;
    node->next = NULL;

    CartItem **slot = &cart->head;              /* append at the end */
    while (*slot != NULL) {
        slot = &(*slot)->next;
    }
    *slot = node;
    return true;
}

CartResult cart_reduce(Cart *cart, int product_id, int quantity, int *remaining)
{
    CartItem **slot = &cart->head;
    while (*slot != NULL && (*slot)->product_id != product_id) {
        slot = &(*slot)->next;
    }

    CartItem *item = *slot;
    if (item == NULL) {
        return CART_NOT_IN_CART;
    }
    if (quantity > item->quantity) {
        return CART_TOO_MANY;
    }

    if (quantity == item->quantity) {
        *slot = item->next;                     /* unlink and free */
        free(item);
        *remaining = 0;
        return CART_REMOVED_ALL;
    }

    item->quantity -= quantity;
    *remaining = item->quantity;
    return CART_REDUCED;
}

void cart_clear(Cart *cart)
{
    CartItem *it = cart->head;
    while (it != NULL) {
        CartItem *next = it->next;
        free(it);
        it = next;
    }
    cart->head = NULL;
}

/* --------------------------- console screens --------------------------- */

static void ui_add(Cart *cart, Catalog *cat)
{
    int id = console_int("\nEnter Product ID to add to cart: ", 1, INT_MAX);
    const Product *p = catalog_find(cat, id);

    if (p == NULL) {
        printf("\nProduct not found.\n");
        return;
    }
    if (p->stock <= 0) {
        printf("\nProduct is out of stock.\n");
        return;
    }

    const CartItem *existing = cart_find(cart, id);
    int already = (existing != NULL) ? existing->quantity : 0;
    int room = p->stock - already;              /* units still addable */

    printf("\nAvailable Stock: %d\n", p->stock);
    if (already > 0) {
        printf("Already in your cart: %d\n", already);
    }
    if (room <= 0) {
        printf("\nYour cart already holds all the available stock.\n");
        return;
    }

    int qty = console_int("Enter Quantity: ", 1, INT_MAX);
    if (qty > room) {
        printf("\nOnly %d more item(s) can be added.\n", room);
        return;
    }

    if (cart_add(cart, id, qty)) {
        printf("\nProduct added to cart successfully!\n");
    } else {
        printf("\nCould not add the product (out of memory).\n");
    }
}

static void ui_view(const Cart *cart, Catalog *cat)
{
    if (cart->head == NULL) {
        printf("\nCart is empty.\n");
        return;
    }

    console_banner("SHOPPING CART");
    for (const CartItem *it = cart->head; it != NULL; it = it->next) {
        const Product *p = catalog_find(cat, it->product_id);
        printf("\nProduct ID : %d\n", it->product_id);
        printf("Name       : %s\n", (p != NULL) ? p->name : "(no longer listed)");
        printf("Quantity   : %d\n", it->quantity);
    }
}

static void ui_remove(Cart *cart)
{
    int id = console_int("\nEnter Product ID to remove from cart: ", 1, INT_MAX);
    const CartItem *item = cart_find(cart, id);

    if (item == NULL) {
        printf("\nProduct not found in cart.\n");
        return;
    }

    printf("Quantity in cart: %d\n", item->quantity);
    int qty = console_int("Enter Quantity to remove: ", 1, INT_MAX);

    int remaining = 0;
    switch (cart_reduce(cart, id, qty, &remaining)) {
        case CART_REDUCED:
            printf("\n%d item(s) removed from cart successfully!\n", qty);
            printf("Remaining Quantity: %d\n", remaining);
            break;
        case CART_REMOVED_ALL:
            printf("\nProduct removed completely from cart!\n");
            break;
        case CART_TOO_MANY:
            printf("\nYou cannot remove more than the quantity in cart.\n");
            break;
        case CART_NOT_IN_CART:
            printf("\nProduct not found in cart.\n");
            break;
    }
}

void cart_menu(Cart *cart, Catalog *cat)
{
    static const char *const options[] = {
        "Add Product to Cart",
        "View Cart",
        "Remove Product from Cart"
    };

    int choice;
    while ((choice = console_menu("SHOPPING CART", options, 3, "Back")) != 0) {
        switch (choice) {
            case 1: ui_add(cart, cat);    break;
            case 2: ui_view(cart, cat);   break;
            case 3: ui_remove(cart);      break;
        }
    }
}
