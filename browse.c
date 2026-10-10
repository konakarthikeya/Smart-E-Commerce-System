#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "browse.h"
#include "console.h"

/* ------------------------------ search ------------------------------ */

/* A "matcher" decides whether a product fits the text the user typed. */
typedef bool (*Matcher)(const Product *p, const char *query);

static bool name_matches(const Product *p, const char *query)
{
    return str_equal_nocase(p->name, query);
}

static bool category_matches(const Product *p, const char *query)
{
    return str_equal_nocase(p->category, query);
}

/* Linear scan that prints every product accepted by the matcher. */
static void print_matches(const Catalog *cat, Matcher matcher, const char *query)
{
    int hits = 0;

    for (int i = 0; i < cat->count; i++) {
        if (matcher(&cat->items[i], query)) {
            printf("\nProduct Found!\n");
            catalog_print_product(&cat->items[i]);
            hits++;
        }
    }
    if (hits == 0) {
        printf("\nProduct not found.\n");
    }
}

static void search_by_id(Catalog *cat)
{
    int id = console_int("\nEnter Product ID: ", 1, INT_MAX);
    const Product *p = catalog_find(cat, id);

    if (p == NULL) {
        printf("\nProduct not found.\n");
        return;
    }
    printf("\nProduct Found!\n");
    catalog_print_product(p);
}

static void search_by_name(Catalog *cat)
{
    char query[50];
    console_text("\nEnter Product Name: ", query, sizeof query);
    print_matches(cat, name_matches, query);
}

static void search_by_category(Catalog *cat)
{
    char query[30];
    console_text("\nEnter Category: ", query, sizeof query);
    print_matches(cat, category_matches, query);
}

/* The BST answers "does this ID exist?" in O(height); the array then
   supplies the product details. */
static void search_by_bst(Catalog *cat)
{
    int id = console_int("\nEnter Product ID: ", 1, INT_MAX);
    const Product *p = NULL;

    if (bst_contains(cat->id_index, id)) {
        p = catalog_find(cat, id);
    }

    if (p == NULL) {
        printf("\nProduct not found.\n");
        return;
    }
    printf("\nProduct Found using BST!\n");
    catalog_print_product(p);
}

void browse_search_menu(Catalog *cat)
{
    static const char *const options[] = {
        "Search by Product ID",
        "Search by Product Name",
        "Search by Category",
        "Search by Product ID using BST"
    };

    int choice;
    while ((choice = console_menu("SEARCH PRODUCTS", options, 4, "Back")) != 0) {
        switch (choice) {
            case 1: search_by_id(cat);       break;
            case 2: search_by_name(cat);     break;
            case 3: search_by_category(cat); break;
            case 4: search_by_bst(cat);      break;
        }
    }
}

/* ------------------------------ sorting ------------------------------ */

/* An "order" answers: must product a be placed before product b? */
typedef bool (*Order)(const Product *a, const Product *b);

static bool cheaper_first(const Product *a, const Product *b)
{
    return a->price < b->price;
}

static bool better_rated_first(const Product *a, const Product *b)
{
    return a->rating > b->rating;
}

static bool name_a_to_z(const Product *a, const Product *b)
{
    return strcmp(a->name, b->name) < 0;
}

/* Selection sort: for each position, pick the item that should come first
   from the unsorted tail and swap it into place. */
static void selection_sort(Product *items, int n, Order goes_before)
{
    for (int pos = 0; pos + 1 < n; pos++) {
        int best = pos;
        for (int j = pos + 1; j < n; j++) {
            if (goes_before(&items[j], &items[best])) {
                best = j;
            }
        }
        if (best != pos) {
            Product tmp = items[pos];
            items[pos] = items[best];
            items[best] = tmp;
        }
    }
}

void browse_sort_menu(Catalog *cat)
{
    static const char *const options[] = {
        "Sort by Price (low to high)",
        "Sort by Rating (high to low)",
        "Sort by Name (A to Z)"
    };
    static const Order orders[] = { cheaper_first, better_rated_first, name_a_to_z };

    int choice;
    while ((choice = console_menu("SORT PRODUCTS", options, 3, "Back")) != 0) {
        selection_sort(cat->items, cat->count, orders[choice - 1]);
        catalog_print_all(cat);
    }
}
