#include <stdio.h>
#include <stdlib.h>
#include "purchase.h"

void purchaseProducts(struct CartNode **cart,
                      struct PurchaseNode **purchaseHistory,
                      struct Product products[],
                      int productCount)
{
    struct CartNode *temp;
    struct PurchaseNode *newNode;
    float totalAmount = 0.0;
    int paymentChoice;
    int found;
    int valid = 1;

    if(*cart == NULL)
    {
        printf("\nCart is empty.\n");
        return;
    }

    /*
       First check whether all products in the cart
       are still available in the required quantity.
    */
    temp = *cart;

    while(temp != NULL)
    {
        found = 0;

        for(int i = 0; i < productCount; i++)
        {
            if(products[i].id == temp->productId)
            {
                found = 1;

                if(products[i].stock < temp->quantity)
                {
                    printf("\nProduct ID %d does not have enough stock.\n",
                           temp->productId);

                    printf("Available Stock : %d\n", products[i].stock);
                    printf("Required Quantity: %d\n", temp->quantity);

                    valid = 0;
                }

                break;
            }
        }

        if(found == 0)
        {
            printf("\nProduct ID %d not found.\n",
                   temp->productId);

            valid = 0;
        }

        temp = temp->next;
    }

    if(valid == 0)
    {
        printf("\nPurchase cannot be completed.\n");
        return;
    }

    /*
       Calculate total amount.
    */
    temp = *cart;

    while(temp != NULL)
    {
        for(int i = 0; i < productCount; i++)
        {
            if(products[i].id == temp->productId)
            {
                totalAmount = totalAmount +
                              (products[i].price * temp->quantity);
                break;
            }
        }

        temp = temp->next;
    }

    /*
       Display bill.
    */
    printf("\n========================================\n");
    printf("              PAYMENT BILL\n");
    printf("========================================\n");

    temp = *cart;

    while(temp != NULL)
    {
        for(int i = 0; i < productCount; i++)
        {
            if(products[i].id == temp->productId)
            {
                printf("\nProduct  : %s\n", products[i].name);
                printf("Quantity : %d\n", temp->quantity);
                printf("Price    : %.2f\n", products[i].price);
                printf("Amount   : %.2f\n",
                       products[i].price * temp->quantity);
                break;
            }
        }

        temp = temp->next;
    }

    printf("\n----------------------------------------\n");
    printf("TOTAL AMOUNT : %.2f\n", totalAmount);
    printf("----------------------------------------\n");

    printf("\n1. Pay\n");
    printf("2. Cancel\n");
    printf("\nEnter your choice: ");
    scanf("%d", &paymentChoice);

    if(paymentChoice != 1)
    {
        printf("\nPayment cancelled.\n");
        return;
    }

    /*
       Payment successful.
       Now decrease stock and create purchase history.
    */
    temp = *cart;

    while(temp != NULL)
    {
        for(int i = 0; i < productCount; i++)
        {
            if(products[i].id == temp->productId)
            {
                products[i].stock =
                    products[i].stock - temp->quantity;

                newNode = (struct PurchaseNode *)
                          malloc(sizeof(struct PurchaseNode));

                newNode->productId = temp->productId;
                newNode->quantity = temp->quantity;
                newNode->amountPaid =
                    products[i].price * temp->quantity;

                newNode->next = *purchaseHistory;
                *purchaseHistory = newNode;

                break;
            }
        }

        temp = temp->next;
    }

    /*
       Clear the cart after successful payment.
    */
    temp = *cart;

    while(temp != NULL)
    {
        struct CartNode *nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    *cart = NULL;

    printf("\nPayment successful!\n");
    printf("Purchase completed successfully!\n");
    printf("Total Paid : %.2f\n", totalAmount);
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
                printf("Quantity   : %d\n", temp->quantity);
                printf("Price      : %.2f\n", products[i].price);
                printf("Amount Paid: %.2f\n", temp->amountPaid);

                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            printf("\nProduct ID : %d\n", temp->productId);
            printf("Quantity   : %d\n", temp->quantity);
            printf("Amount Paid: %.2f\n", temp->amountPaid);
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
            printf("Quantity   : %d\n", temp->quantity);
            printf("Amount Paid: %.2f\n", temp->amountPaid);

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