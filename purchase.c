#include <stdio.h>
#include <stdlib.h>
#include "purchase.h"

void purchaseProducts(struct CartNode **cart,
                      struct PurchaseNode **purchaseHistory,
                      struct Product products[],
                      int productCount)
{
    struct CartNode *temp;
    struct CartNode *prev;
    struct PurchaseNode *newNode;
    int found;

    if(*cart == NULL)
    {
        printf("\nCart is empty.\n");
        return;
    }

    temp = *cart;
    prev = NULL;

    while(temp != NULL)
    {
        found = 0;

        for(int i = 0; i < productCount; i++)
        {
            if(products[i].id == temp->productId)
            {
                found = 1;

                if(products[i].stock > 0)
                {
                    products[i].stock--;

                    newNode = (struct PurchaseNode *)
                              malloc(sizeof(struct PurchaseNode));

                    newNode->productId = temp->productId;
                    newNode->next = *purchaseHistory;
                    *purchaseHistory = newNode;

                    if(prev == NULL)
                    {
                        *cart = temp->next;
                        free(temp);
                        temp = *cart;
                    }
                    else
                    {
                        prev->next = temp->next;
                        free(temp);
                        temp = prev->next;
                    }
                }
                else
                {
                    printf("\nProduct ID %d is out of stock.\n",
                           temp->productId);

                    prev = temp;
                    temp = temp->next;
                }

                break;
            }
        }

        if(found == 0)
        {
            printf("\nProduct ID %d not found.\n",
                   temp->productId);

            if(prev == NULL)
            {
                *cart = temp->next;
                free(temp);
                temp = *cart;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        }
    }

    printf("\nPurchase completed successfully!\n");
}

void displayPurchaseHistory(struct PurchaseNode *purchaseHistory,
                            struct Product products[],
                            int productCount)
{
    struct PurchaseNode *temp;
    int found;

    if(purchaseHistory == NULL)
    {
        printf("\nNo purchase history available.\n");
        return;
    }

    printf("\n========================================\n");
    printf("          PURCHASE HISTORY\n");
    printf("========================================\n");

    temp = purchaseHistory;

    while(temp != NULL)
    {
        found = 0;

        for(int i = 0; i < productCount; i++)
        {
            if(products[i].id == temp->productId)
            {
                printf("\nProduct ID : %d\n", products[i].id);
                printf("Name       : %s\n", products[i].name);
                printf("Category   : %s\n", products[i].category);
                printf("Price      : %.2f\n", products[i].price);

                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            printf("\nProduct ID : %d\n", temp->productId);
            printf("Product details no longer available.\n");
        }

        temp = temp->next;
    }
}

void searchPurchaseHistory(struct PurchaseNode *purchaseHistory,
                           struct Product products[],
                           int productCount)
{
    int id;
    int found = 0;
    struct PurchaseNode *temp;

    printf("\nEnter Product ID to search: ");
    scanf("%d", &id);

    temp = purchaseHistory;

    while(temp != NULL)
    {
        if(temp->productId == id)
        {
            printf("\nProduct found in purchase history.\n");

            for(int i = 0; i < productCount; i++)
            {
                if(products[i].id == id)
                {
                    printf("ID       : %d\n", products[i].id);
                    printf("Name     : %s\n", products[i].name);
                    printf("Category : %s\n", products[i].category);
                    printf("Price    : %.2f\n", products[i].price);
                    break;
                }
            }

            found = 1;
            break;
        }

        temp = temp->next;
    }

    if(found == 0)
    {
        printf("\nProduct not found in purchase history.\n");
    }
}
