#ifndef RECOMMEND_H
#define RECOMMEND_H

#include "orders.h"
#include "catalog.h"

/* For every distinct product in the purchase history, list in-stock
   products that are not yet bought, from most to least similar. */
void recommend_show(const History *history, Catalog *cat);

#endif
