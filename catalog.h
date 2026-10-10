#ifndef CATALOG_H
#define CATALOG_H

#include <stdbool.h>
#include "models.h"
#include "bst.h"

/* All products live here, together with a BST index of their IDs. */
typedef struct {
    Product  items[MAX_PRODUCTS];
    int      count;
    BstNode *id_index;
} Catalog;

/* ---- data operations (no printing) ---- */
void     catalog_destroy(Catalog *cat);
int      catalog_index_of(const Catalog *cat, int id);   /* -1 if absent */
Product *catalog_find(Catalog *cat, int id);             /* NULL if absent */
bool     catalog_insert(Catalog *cat, const Product *p); /* false: full/duplicate */
bool     catalog_remove(Catalog *cat, int id);

/* ---- console screens ---- */
void catalog_print_product(const Product *p);
void catalog_print_all(const Catalog *cat);
void catalog_ui_add(Catalog *cat);
void catalog_ui_update(Catalog *cat);
void catalog_ui_remove(Catalog *cat);
void catalog_ui_show_index(const Catalog *cat);

#endif
