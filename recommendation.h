#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include "structures.h"

void showRecommendations(struct PurchaseNode *purchaseHistory,
                         struct Product products[],
                         int productCount);

#endif