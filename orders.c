#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "orders.h"
#include "console.h"

/* --------------------------- history list --------------------------- */

static bool history_record(History *history, int product_id, int quantity, float paid)
{
    Receipt *node = malloc(sizeof *node);
    if (node == NULL) {
        return false;
    }
    node->product_id = product_id;
    node->quantity = quantity;
    node->amount_paid = paid;
    node->next = NULL;

    if (history->tail == NULL) {
        history->head = node;
    } else {
        history->tail->next = node;
    }
    history->tail = node;
    return true;
}

void history_destroy(History *history)
{
    Receipt *r = history->head;
    while (r != NULL) {
        Receipt *next = r->next;
        free(r);
        r = next;
    }
    history->head = NULL;
    history->tail = NULL;
}

/* ----------------------------- checkout ----------------------------- */

/* Every cart line must still exist and be in stock.  All problems are
   reported (not just the first) so the customer can fix them in one go. */
static bool cart_is_payable(const Cart *cart, Catalog *cat)
{
    bool ok = true;

    for (const CartItem *it = cart->head; it != NULL; it = it->next) {
        const Product *p = catalog_find(cat, it->product_id);

        if (p == NULL) {
            printf("\nProduct ID %d is no longer available.\n", it->product_id);
            ok = false;
        } else if (p->stock < it->quantity) {
            printf("\nProduct ID %d does not have enough stock.\n", it->product_id);
            printf("Available Stock  : %d\n", p->stock);
            printf("Required Quantity: %d\n", it->quantity);
            ok = false;
        }
    }
    return ok;
}

/* Prints the bill and returns the grand total.  Call only after
   cart_is_payable() succeeded, so every product is guaranteed to exist. */
static float print_bill(const Cart *cart, Catalog *cat)
{
    float total = 0.0f;

    console_banner("PAYMENT BILL");
    for (const CartItem *it = cart->head; it != NULL; it = it->next) {
        const Product *p = catalog_find(cat, it->product_id);
        float line_total = p->price * (float)it->quantity;

        printf("\nProduct  : %s\n", p->name);
        printf("Quantity : %d\n", it->quantity);
        printf("Price    : %.2f\n", p->price);
        printf("Amount   : %.2f\n", line_total);
        total += line_total;
    }

    printf("\n----------------------------------------\n");
    printf("TOTAL AMOUNT : %.2f\n", total);
    printf("----------------------------------------\n");
    return total;
}

void orders_checkout(Cart *cart, History *history, Catalog *cat)
{
    if (cart->head == NULL) {
        printf("\nCart is empty.\n");
        return;
    }
    if (!cart_is_payable(cart, cat)) {
        printf("\nPurchase cannot be completed.\n");
        return;
    }

    float total = print_bill(cart, cat);

    printf("\n1. Pay\n2. Cancel\n\n");
    if (console_int("Enter your choice: ", 1, 2) != 1) {
        printf("\nPayment cancelled.\n");
        return;
    }

    for (const CartItem *it = cart->head; it != NULL; it = it->next) {
        Product *p = catalog_find(cat, it->product_id);
        float paid = p->price * (float)it->quantity;

        p->stock -= it->quantity;
        if (!history_record(history, p->id, it->quantity, paid)) {
            printf("\nWarning: could not record product %d in history.\n", p->id);
        }
    }
    cart_clear(cart);

    printf("\nPayment successful!\n");
    printf("Purchase completed successfully!\n");
    printf("Total Paid : %.2f\n", total);
}

/* ----------------------------- history ----------------------------- */

static void print_receipt(const Receipt *r, Catalog *cat)
{
    const Product *p = catalog_find(cat, r->product_id);

    printf("\nProduct ID : %d\n", r->product_id);
    if (p != NULL) {
        printf("Name       : %s\n", p->name);
        printf("Category   : %s\n", p->category);
        printf("Price      : %.2f\n", p->price);
    }
    printf("Quantity   : %d\n", r->quantity);
    printf("Amount Paid: %.2f\n", r->amount_paid);
    if (p == NULL) {
        printf("Product details no longer available.\n");
    }
}

static void ui_display(const History *history, Catalog *cat)
{
    if (history->head == NULL) {
        printf("\nNo purchase history available.\n");
        return;
    }

    console_banner("PURCHASE HISTORY");
    for (const Receipt *r = history->head; r != NULL; r = r->next) {
        print_receipt(r, cat);
    }
}

static void ui_search(const History *history, Catalog *cat)
{
    int id = console_int("\nEnter Product ID to search: ", 1, INT_MAX);
    int hits = 0;

    for (const Receipt *r = history->head; r != NULL; r = r->next) {
        if (r->product_id == id) {
            if (hits == 0) {
                printf("\nProduct found in purchase history.\n");
            }
            print_receipt(r, cat);
            hits++;
        }
    }
    if (hits == 0) {
        printf("\nProduct not found in purchase history.\n");
    }
}

void history_menu(const History *history, Catalog *cat)
{
    static const char *const options[] = {
        "Display Purchase History",
        "Search Purchase History"
    };

    int choice;
    while ((choice = console_menu("PURCHASE HISTORY", options, 2, "Back")) != 0) {
        if (choice == 1) {
            ui_display(history, cat);
        } else {
            ui_search(history, cat);
        }
    }
}
