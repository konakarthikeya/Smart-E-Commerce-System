#include <stdio.h>
#include "customer.h"

void addCustomer(struct Customer customers[], int *customerCount)
{
    if(*customerCount < 100)
    {
        printf("\nEnter Customer ID: ");
        scanf("%d", &customers[*customerCount].id);

        printf("Enter Customer Name: ");
        scanf("%s", customers[*customerCount].name);

        printf("Enter Phone Number: ");
        scanf("%s", customers[*customerCount].phone);

        printf("Enter Email: ");
        scanf("%s", customers[*customerCount].email);

        (*customerCount)++;

        printf("\nCustomer added successfully!\n");
    }
    else
    {
        printf("\nCustomer storage is full!\n");
    }
}

void displayCustomers(struct Customer customers[], int customerCount)
{
    if(customerCount == 0)
    {
        printf("\nNo customers available.\n");
    }
    else
    {
        printf("\n========================================\n");
        printf("          CUSTOMER LIST\n");
        printf("========================================\n");

        for(int i = 0; i < customerCount; i++)
        {
            printf("\nCustomer %d\n", i + 1);
            printf("ID    : %d\n", customers[i].id);
            printf("Name  : %s\n", customers[i].name);
            printf("Phone : %s\n", customers[i].phone);
            printf("Email : %s\n", customers[i].email);
        }
    }
}

void searchCustomer(struct Customer customers[], int customerCount)
{
    int searchId;
    int found = 0;

    printf("\nEnter Customer ID: ");
    scanf("%d", &searchId);

    for(int i = 0; i < customerCount; i++)
    {
        if(customers[i].id == searchId)
        {
            printf("\nCustomer Found!\n");
            printf("ID    : %d\n", customers[i].id);
            printf("Name  : %s\n", customers[i].name);
            printf("Phone : %s\n", customers[i].phone);
            printf("Email : %s\n", customers[i].email);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nCustomer not found.\n");
    }
}

void updateCustomer(struct Customer customers[], int customerCount)
{
    int updateId;
    int found = 0;

    printf("\nEnter Customer ID to update: ");
    scanf("%d", &updateId);

    for(int i = 0; i < customerCount; i++)
    {
        if(customers[i].id == updateId)
        {
            printf("\nCurrent Customer Details\n");
            printf("----------------------------\n");
            printf("ID    : %d\n", customers[i].id);
            printf("Name  : %s\n", customers[i].name);
            printf("Phone : %s\n", customers[i].phone);
            printf("Email : %s\n", customers[i].email);

            printf("\nEnter New Customer Name: ");
            scanf("%s", customers[i].name);

            printf("Enter New Phone: ");
            scanf("%s", customers[i].phone);

            printf("Enter New Email: ");
            scanf("%s", customers[i].email);

            printf("\nCustomer updated successfully!\n");

            printf("\nUpdated Customer Details\n");
            printf("----------------------------\n");
            printf("ID    : %d\n", customers[i].id);
            printf("Name  : %s\n", customers[i].name);
            printf("Phone : %s\n", customers[i].phone);
            printf("Email : %s\n", customers[i].email);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nCustomer not found.\n");
    }
}

void deleteCustomer(struct Customer customers[], int *customerCount)
{
    int deleteId;
    int found = 0;

    printf("\nEnter Customer ID to delete: ");
    scanf("%d", &deleteId);

    for(int i = 0; i < *customerCount; i++)
    {
        if(customers[i].id == deleteId)
        {
            for(int j = i; j < *customerCount - 1; j++)
            {
                customers[j] = customers[j + 1];
            }

            (*customerCount)--;

            printf("\nCustomer deleted successfully!\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nCustomer not found.\n");
    }
}