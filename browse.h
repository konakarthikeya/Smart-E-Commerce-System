#ifndef BROWSE_H
#define BROWSE_H

#include "catalog.h"

/* Sub-menu: search by ID / name / category / ID through the BST. */
void browse_search_menu(Catalog *cat);

/* Sub-menu: selection-sort the catalog by price, rating or name. */
void browse_sort_menu(Catalog *cat);

#endif
