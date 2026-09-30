#include <stdio.h>
#include <stdlib.h>
#include "cart.h"

void addToCart(struct CartNode **cart, struct Product products[], int productCount)
{
    int id;
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

            if(products[i].stock <= 0)
            {
                printf("\nProduct is out of stock.\n");
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
        temp = temp->next;
    }
}

void removeFromCart(struct CartNode **cart)
{
    int id;
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
            if(prev == NULL)
            {
                *cart = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }

            free(temp);

            printf("\nProduct removed from cart successfully!\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nProduct not found in cart.\n");
}
