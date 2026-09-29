#include <stdio.h>
#include <string.h>
#include "recommendation.h"

void showRecommendations(struct PurchaseNode *purchaseHistory,
                         struct Product products[],
                         int productCount)
{
    struct PurchaseNode *temp;
    int shownIds[100];
    int shownCount = 0;

    if(purchaseHistory == NULL)
    {
        printf("\nNo purchase history available.\n");
        return;
    }

    printf("\n========================================\n");
    printf("          RECOMMENDATIONS\n");
    printf("========================================\n");

    temp = purchaseHistory;

    while(temp != NULL)
    {
        int purchasedIndex = -1;

        for(int i = 0; i < productCount; i++)
        {
            if(products[i].id == temp->productId)
            {
                purchasedIndex = i;
                break;
            }
        }

        if(purchasedIndex != -1)
        {
            printf("\nBased on: %s %s\n",
                   products[purchasedIndex].brand,
                   products[purchasedIndex].name);

            /*
             * LEVEL 1
             * Same brand + same type
             */
            printf("\nSame Brand and Type:\n");

            int level1Found = 0;

            for(int i = 0; i < productCount; i++)
            {
                if(i != purchasedIndex &&
                   products[i].stock > 0 &&
                   strcmp(products[i].brand,
                          products[purchasedIndex].brand) == 0 &&
                   strcmp(products[i].type,
                          products[purchasedIndex].type) == 0)
                {
                    int alreadyShown = 0;

                    for(int j = 0; j < shownCount; j++)
                    {
                        if(shownIds[j] == products[i].id)
                        {
                            alreadyShown = 1;
                            break;
                        }
                    }

                    if(alreadyShown == 0)
                    {
                        printf("  %s %s (ID: %d)\n",
                               products[i].brand,
                               products[i].name,
                               products[i].id);

                        shownIds[shownCount] = products[i].id;
                        shownCount++;
                        level1Found = 1;
                    }
                }
            }

            if(level1Found == 0)
            {
                printf("  No products available.\n");
            }

            /*
             * LEVEL 2
             * Same product type, different brands
             */
            printf("\nOther %s Products:\n",
                   products[purchasedIndex].type);

            int level2Found = 0;

            for(int i = 0; i < productCount; i++)
            {
                if(i != purchasedIndex &&
                   products[i].stock > 0 &&
                   strcmp(products[i].type,
                          products[purchasedIndex].type) == 0)
                {
                    int alreadyShown = 0;

                    for(int j = 0; j < shownCount; j++)
                    {
                        if(shownIds[j] == products[i].id)
                        {
                            alreadyShown = 1;
                            break;
                        }
                    }

                    if(alreadyShown == 0)
                    {
                        printf("  %s %s (ID: %d)\n",
                               products[i].brand,
                               products[i].name,
                               products[i].id);

                        shownIds[shownCount] = products[i].id;
                        shownCount++;
                        level2Found = 1;
                    }
                }
            }

            if(level2Found == 0)
            {
                printf("  No products available.\n");
            }

            /*
             * LEVEL 3
             * Same category
             */
            printf("\nOther %s Products:\n",
                   products[purchasedIndex].category);

            int level3Found = 0;

            for(int i = 0; i < productCount; i++)
            {
                if(i != purchasedIndex &&
                   products[i].stock > 0 &&
                   strcmp(products[i].category,
                          products[purchasedIndex].category) == 0)
                {
                    int alreadyShown = 0;

                    for(int j = 0; j < shownCount; j++)
                    {
                        if(shownIds[j] == products[i].id)
                        {
                            alreadyShown = 1;
                            break;
                        }
                    }

                    if(alreadyShown == 0)
                    {
                        printf("  %s %s (ID: %d)\n",
                               products[i].brand,
                               products[i].name,
                               products[i].id);

                        shownIds[shownCount] = products[i].id;
                        shownCount++;
                        level3Found = 1;
                    }
                }
            }

            if(level3Found == 0)
            {
                printf("  No products available.\n");
            }
        }

        temp = temp->next;
    }
}