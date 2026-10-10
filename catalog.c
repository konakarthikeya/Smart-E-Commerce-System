#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "catalog.h"
#include "console.h"

/* ------------------------- data operations ------------------------- */

void catalog_destroy(Catalog *cat)
{
    bst_destroy(cat->id_index);
    cat->id_index = NULL;
    cat->count = 0;
}

int catalog_index_of(const Catalog *cat, int id)
{
    for (int i = 0; i < cat->count; i++) {
        if (cat->items[i].id == id) {
            return i;
        }
    }
    return -1;
}

Product *catalog_find(Catalog *cat, int id)
{
    int idx = catalog_index_of(cat, id);
    return (idx < 0) ? NULL : &cat->items[idx];
}

bool catalog_insert(Catalog *cat, const Product *p)
{
    if (cat->count >= MAX_PRODUCTS || catalog_index_of(cat, p->id) >= 0) {
        return false;
    }
    cat->items[cat->count++] = *p;
    cat->id_index = bst_insert(cat->id_index, p->id);
    return true;
}

bool catalog_remove(Catalog *cat, int id)
{
    int idx = catalog_index_of(cat, id);
    if (idx < 0) {
        return false;
    }

    int tail = cat->count - idx - 1;            /* items after the gap */
    memmove(&cat->items[idx], &cat->items[idx + 1], (size_t)tail * sizeof(Product));
    cat->count--;

    cat->id_index = bst_remove(cat->id_index, id);
    return true;
}

/* --------------------------- console screens --------------------------- */

void catalog_print_product(const Product *p)
{
    printf("ID       : %d\n",   p->id);
    printf("Brand    : %s\n",   p->brand);
    printf("Name     : %s\n",   p->name);
    printf("Type     : %s\n",   p->type);
    printf("Category : %s\n",   p->category);
    printf("Price    : %.2f\n", p->price);
    printf("Rating   : %.2f\n", p->rating);
    printf("Stock    : %d\n",   p->stock);
}

void catalog_print_all(const Catalog *cat)
{
    if (cat->count == 0) {
        printf("\nNo products available.\n");
        return;
    }

    console_banner("PRODUCT LIST");
    for (int i = 0; i < cat->count; i++) {
        printf("\n");
        catalog_print_product(&cat->items[i]);
    }
}

/* Asks for every editable field; used by both "add" and "update". */
static void read_product_details(Product *p)
{
    console_text("Enter Brand: ",        p->brand,    sizeof p->brand);
    console_text("Enter Product Name: ",  p->name,     sizeof p->name);
    console_text("Enter Product Type: ",  p->type,     sizeof p->type);
    console_text("Enter Category: ",      p->category, sizeof p->category);
    p->price  = console_float("Enter Price: ",  0.0f, 10000000.0f);
    p->rating = console_float("Enter Rating (0-5): ", 0.0f, 5.0f);
    p->stock  = console_int("Enter Stock: ", 0, 1000000);
}

void catalog_ui_add(Catalog *cat)
{
    if (cat->count >= MAX_PRODUCTS) {
        printf("\nProduct storage is full!\n");
        return;
    }

    Product p;
    for (;;) {
        p.id = console_int("\nEnter Product ID: ", 1, INT_MAX);
        if (catalog_index_of(cat, p.id) < 0) {
            break;
        }
        printf("Product ID already exists. Please enter a different one.\n");
    }

    read_product_details(&p);
    catalog_insert(cat, &p);
    printf("\nProduct added successfully!\n");
}

void catalog_ui_update(Catalog *cat)
{
    int id = console_int("\nEnter Product ID to update: ", 1, INT_MAX);
    Product *p = catalog_find(cat, id);

    if (p == NULL) {
        printf("\nProduct not found.\n");
        return;
    }

    printf("\nCurrent details:\n");
    catalog_print_product(p);

    printf("\nEnter the new details (the ID stays the same).\n");
    read_product_details(p);
    printf("\nProduct updated successfully!\n");
}

void catalog_ui_remove(Catalog *cat)
{
    int id = console_int("\nEnter Product ID to delete: ", 1, INT_MAX);

    if (catalog_remove(cat, id)) {
        printf("\nProduct deleted successfully!\n");
    } else {
        printf("\nProduct not found.\n");
    }
}

void catalog_ui_show_index(const Catalog *cat)
{
    printf("\nBST Inorder Traversal: ");
    bst_print_inorder(cat->id_index);
    printf("\n");
}
