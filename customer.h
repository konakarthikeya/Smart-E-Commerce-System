#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "models.h"

typedef struct {
    Customer items[MAX_CUSTOMERS];
    int      count;
} CustomerBook;

/* Sub-menu: add / display / search / update / delete customers. */
void customer_menu(CustomerBook *book);

#endif
