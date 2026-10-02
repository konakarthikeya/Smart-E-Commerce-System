#include <stdio.h>
#include <string.h>
#include "search_sort.h"
#include "input.h"

int compareIgnoreCase(char str1[], char str2[])
{
    int i = 0;

    while(str1[i] != '\0' && str2[i] != '\0')
    {
        char c1 = str1[i];
        char c2 = str2[i];

        if(c1 >= 'A' && c1 <= 'Z')
            c1 = c1 + 32;

        if(c2 >= 'A' && c2 <= 'Z')
            c2 = c2 + 32;

        if(c1 != c2)
            return 0;

        i++;
    }

    if(str1[i] == '\0' && str2[i] == '\0')
        return 1;

    return 0;
}

void searchProductById(struct Product products[], int productCount)
{
    int id;
    int found = 0;

    printf("\nEnter Product ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    for(int i = 0; i < productCount; i++)
    {
        if(products[i].id == id)
        {
            printf("\nProduct Found!\n");
            printf("ID       : %d\n", products[i].id);
            printf("Brand    : %s\n", products[i].brand);
            printf("Name     : %s\n", products[i].name);
            printf("Type     : %s\n", products[i].type);
            printf("Category : %s\n", products[i].category);
            printf("Price    : %.2f\n", products[i].price);
            printf("Rating   : %.2f\n", products[i].rating);
            printf("Stock    : %d\n", products[i].stock);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nProduct not found.\n");
    }
}

void searchProductByName(struct Product products[], int productCount)
{
    char name[50];
    int found = 0;

    printf("\nEnter Product Name: ");
    readString(name, 50);

    for(int i = 0; i < productCount; i++)
    {
        if(compareIgnoreCase(products[i].name, name))
        {
            printf("\nProduct Found!\n");
            printf("ID       : %d\n", products[i].id);
            printf("Brand    : %s\n", products[i].brand);
            printf("Name     : %s\n", products[i].name);
            printf("Type     : %s\n", products[i].type);
            printf("Category : %s\n", products[i].category);
            printf("Price    : %.2f\n", products[i].price);
            printf("Rating   : %.2f\n", products[i].rating);
            printf("Stock    : %d\n", products[i].stock);

            found = 1;
        }
    }

    if(found == 0)
    {
        printf("\nProduct not found.\n");
    }
}

void searchProductByCategory(struct Product products[], int productCount)
{
    char category[30];
    int found = 0;

    printf("\nEnter Category: ");
    readString(category, 30);

    for(int i = 0; i < productCount; i++)
    {
        if(strcmp(products[i].category, category) == 0)
        {
            printf("\nProduct Found!\n");
            printf("ID       : %d\n", products[i].id);
            printf("Brand    : %s\n", products[i].brand);
            printf("Name     : %s\n", products[i].name);
            printf("Type     : %s\n", products[i].type);
            printf("Category : %s\n", products[i].category);
            printf("Price    : %.2f\n", products[i].price);
            printf("Rating   : %.2f\n", products[i].rating);
            printf("Stock    : %d\n", products[i].stock);

            found = 1;
        }
    }

    if(found == 0)
    {
        printf("\nProduct not found.\n");
    }
}

void searchProductByBST(struct Product products[], int productCount, struct BSTNode *root)
{
    int id;
    int found = 0;
    struct BSTNode *result;

    printf("\nEnter Product ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    result = searchBST(root, id);

    if(result != NULL)
    {
        for(int i = 0; i < productCount; i++)
        {
            if(products[i].id == id)
            {
                printf("\nProduct Found using BST!\n");
                printf("ID       : %d\n", products[i].id);
                printf("Brand    : %s\n", products[i].brand);
                printf("Name     : %s\n", products[i].name);
                printf("Type     : %s\n", products[i].type);
                printf("Category : %s\n", products[i].category);
                printf("Price    : %.2f\n", products[i].price);
                printf("Rating   : %.2f\n", products[i].rating);
                printf("Stock    : %d\n", products[i].stock);

                found = 1;
                break;
            }
        }
    }

    if(found == 0)
    {
        printf("\nProduct not found.\n");
    }
}

void sortByPrice(struct Product products[], int productCount)
{
    int i, j, min;
    struct Product temp;

    for(i = 0; i < productCount - 1; i++)
    {
        min = i;

        for(j = i + 1; j < productCount; j++)
        {
            if(products[j].price < products[min].price)
            {
                min = j;
            }
        }

        if(min != i)
        {
            temp = products[i];
            products[i] = products[min];
            products[min] = temp;
        }
    }
}

void sortByRating(struct Product products[], int productCount)
{
    int i, j, max;
    struct Product temp;

    for(i = 0; i < productCount - 1; i++)
    {
        max = i;

        for(j = i + 1; j < productCount; j++)
        {
            if(products[j].rating > products[max].rating)
            {
                max = j;
            }
        }

        if(max != i)
        {
            temp = products[i];
            products[i] = products[max];
            products[max] = temp;
        }
    }
}

void sortByName(struct Product products[], int productCount)
{
    int i, j, min;
    struct Product temp;

    for(i = 0; i < productCount - 1; i++)
    {
        min = i;

        for(j = i + 1; j < productCount; j++)
        {
            if(strcmp(products[j].name, products[min].name) < 0)
            {
                min = j;
            }
        }

        if(min != i)
        {
            temp = products[i];
            products[i] = products[min];
            products[min] = temp;
        }
    }
}