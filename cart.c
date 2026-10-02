#include <stdio.h>
#include <stdlib.h>
#include "cart.h"

void addToCart(struct CartNode **cart, struct Product products[], int productCount)
{
    int id;
    int quantity;
    int found = 0;
    int alreadyInCart = 0;
    struct CartNode *temp;
    struct CartNode *newNode;

    printf("\nEnter Product ID to add to cart: ");
    scanf("%d", &id);

    for(int i = 0; i < productCount; i++)
    {
        if(products[i].id == id)
        {
            found = 1;

            printf("\nAvailable Stock: %d\n", products[i].stock);

            if(products[i].stock <= 0)
            {
                printf("\nProduct is out of stock.\n");
                return;
            }

            printf("Enter Quantity: ");
            scanf("%d", &quantity);

            if(quantity <= 0)
            {
                printf("\nInvalid quantity.\n");
                return;
            }

            if(quantity > products[i].stock)
            {
                printf("\nOnly %d items are available in stock.\n",
                       products[i].stock);
                return;
            }

            break;
        }
    }

    if(found == 0)
    {
        printf("\nProduct not found.\n");
        return;
    }

    temp = *cart;

    while(temp != NULL)
    {
        if(temp->productId == id)
        {
            alreadyInCart = 1;
            break;
        }

        temp = temp->next;
    }

    if(alreadyInCart == 1)
    {
        printf("\nProduct is already in cart.\n");
        return;
    }

    newNode = (struct CartNode *)malloc(sizeof(struct CartNode));

    newNode->productId = id;
    newNode->quantity = quantity;
    newNode->next = *cart;
    *cart = newNode;

    printf("\nProduct added to cart successfully!\n");
}
void viewCart(struct CartNode *cart)
{
    struct CartNode *temp;

    if(cart == NULL)
    {
        printf("\nCart is empty.\n");
        return;
    }

    printf("\n========================================\n");
    printf("             SHOPPING CART\n");
    printf("========================================\n");

    temp = cart;

    while(temp != NULL)
    {
        printf("Product ID : %d\n", temp->productId);
        printf("Quantity   : %d\n", temp->quantity);
        temp = temp->next;
    }
}

void removeFromCart(struct CartNode **cart)
{
    int id;
    int quantity;
    struct CartNode *temp;
    struct CartNode *prev;

    printf("\nEnter Product ID to remove from cart: ");
    scanf("%d", &id);

    temp = *cart;
    prev = NULL;

    while(temp != NULL)
    {
        if(temp->productId == id)
        {
            printf("Quantity in cart: %d\n", temp->quantity);
            printf("Enter Quantity to remove: ");
            scanf("%d", &quantity);

            if(quantity <= 0)
            {
                printf("\nInvalid quantity.\n");
                return;
            }

            if(quantity > temp->quantity)
            {
                printf("\nYou cannot remove more than the quantity in cart.\n");
                return;
            }

            if(quantity < temp->quantity)
            {
                temp->quantity = temp->quantity - quantity;

                printf("\n%d item(s) removed from cart successfully!\n",
                       quantity);
                printf("Remaining Quantity: %d\n", temp->quantity);
                return;
            }

            if(quantity == temp->quantity)
            {
                if(prev == NULL)
                {
                    *cart = temp->next;
                }
                else
                {
                    prev->next = temp->next;
                }

                free(temp);

                printf("\nProduct removed completely from cart!\n");
                return;
            }
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nProduct not found in cart.\n");
}
