#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "bst.h"
#include "cart.h"
#include "purchase.h"
#include "customer.h"
#include "search_sort.h"
#include "recommendation.h"

int main()
{
    struct Customer customers[100];
    int customerCount = 0;

    int choice;

    struct CartNode *cart = NULL;
    struct PurchaseNode *purchaseHistory = NULL;

    struct Product products[100];
    int productCount = 0;

    struct BSTNode *root = NULL;

    do
    {
        printf("\n========================================\n");
        printf("       SMART E-COMMERCE SYSTEM\n");
        printf("             VERSION 1.0\n");
        printf("========================================\n\n");

        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Products\n");
        printf("4. Sort Products\n");
        printf("5. Shopping Cart\n");
        printf("6. Purchase Products\n");
        printf("7. Purchase History\n");
        printf("8. Recommendations\n");
        printf("9. Customer Management\n");
         printf("10. Display BST (Inorder)\n"); 
        printf("11. Update Product\n"); 
        printf("12. Delete Product\n"); 
        printf("0. Exit\n\n"); 

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
{
    int newId;
    int duplicate;

    if(productCount < 100)
    {
        do
        {
            duplicate = 0;

            printf("\nEnter Product ID: ");
            scanf("%d", &newId);

            for(int i = 0; i < productCount; i++)
            {
                if(products[i].id == newId)
                {
                    duplicate = 1;
                    break;
                }
            }

            if(duplicate == 1)
            {
                printf("\nProduct ID already exists!\n");
                printf("Please enter a different Product ID.\n");
            }

        } while(duplicate == 1);

        products[productCount].id = newId;

printf("Enter Brand: ");
scanf("%s", products[productCount].brand);

printf("Enter Product Name: ");
scanf("%s", products[productCount].name);

printf("Enter Product Type: ");
scanf("%s", products[productCount].type);

printf("Enter Category: ");
scanf("%s", products[productCount].category);

printf("Enter Price: ");
scanf("%f", &products[productCount].price);

printf("Enter Rating: ");
scanf("%f", &products[productCount].rating);

printf("Enter Stock: ");
scanf("%d", &products[productCount].stock);

        root = insertBST(root, newId);

        productCount++;

        printf("\nProduct added successfully!\n");
    }
    else
    {
        printf("\nProduct storage is full!\n");
    }

    break;
}

            case 2:
                if(productCount == 0)
                {
                    printf("\nNo products available.\n");
                }
                else
                {
                    printf("\n========================================\n");
                    printf("          PRODUCT LIST\n");
                    printf("========================================\n");

                    for(int i = 0; i < productCount; i++)
                    {
                       printf("ID       : %d\n", products[i].id);
printf("Brand    : %s\n", products[i].brand);
printf("Name     : %s\n", products[i].name);
printf("Type     : %s\n", products[i].type);
printf("Category : %s\n", products[i].category);
printf("Price    : %.2f\n", products[i].price);
printf("Rating   : %.2f\n", products[i].rating);
printf("Stock    : %d\n", products[i].stock);
                    }
                }

                break;

         case 3:
{
    int searchChoice;

    do
    {
        printf("\n========================================\n");
        printf("           SEARCH PRODUCTS\n");
        printf("========================================\n\n");

        printf("1. Search by Product ID\n");
        printf("2. Search by Product Name\n");
        printf("3. Search by Category\n");
        printf("4. Search by Product ID using BST\n");
        printf("0. Back\n\n");

        printf("Enter your choice: ");
        scanf("%d", &searchChoice);

        switch(searchChoice)
        {
            case 1:
                searchProductById(products, productCount);
                break;

            case 2:
                searchProductByName(products, productCount);
                break;

            case 3:
                searchProductByCategory(products, productCount);
                break;

            case 4:
                searchProductByBST(products, productCount, root);
                break;

            case 0:
                printf("\nReturning to main menu...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(searchChoice != 0);

    break;
}
          case 4:
{
    int sortChoice;

    do
    {
        printf("\n========================================\n");
        printf("           SORT PRODUCTS\n");
        printf("========================================\n\n");

        printf("1. Sort by Price\n");
        printf("2. Sort by Rating\n");
        printf("3. Sort by Name\n");
        printf("0. Back\n\n");

        printf("Enter your choice: ");
        scanf("%d", &sortChoice);

        switch(sortChoice)
        {
            case 1:
                sortByPrice(products, productCount);
                break;

            case 2:
                sortByRating(products, productCount);
                break;

            case 3:
                sortByName(products, productCount);
                break;

            case 0:
                printf("\nReturning to main menu...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(sortChoice != 0);

    break;
}
            case 5:
{
    int cartChoice;

    do
    {
        printf("\n========================================\n");
        printf("           SHOPPING CART\n");
        printf("========================================\n\n");

        printf("1. Add Product to Cart\n");
        printf("2. View Cart\n");
        printf("3. Remove Product from Cart\n");
        printf("0. Back\n\n");

        printf("Enter your choice: ");
        scanf("%d", &cartChoice);

        switch(cartChoice)
        {
            case 1:
                addToCart(&cart, products, productCount);
                break;

            case 2:
                viewCart(cart);
                break;

            case 3:
                removeFromCart(&cart);
                break;

            case 0:
                printf("\nReturning to main menu...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(cartChoice != 0);

    break;
}
           case 6:
{
    purchaseProducts(&cart,
                     &purchaseHistory,
                     products,
                     productCount);

    break;
}
           case 7:
{
    int choice7;

    do
    {
        printf("\n===== PURCHASE HISTORY =====\n");
        printf("1. Display Purchase History\n");
        printf("2. Search Purchase History\n");
        printf("0. Back\n");

        printf("Enter your choice: ");
        scanf("%d", &choice7);

        switch(choice7)
        {
            case 1:
                displayPurchaseHistory(purchaseHistory,
                                       products,
                                       productCount);
                break;

            case 2:
                searchPurchaseHistory(purchaseHistory,
                                      products,
                                      productCount);
                break;

            case 0:
                break;

            default:
                printf("\nInvalid choice.\n");
        }

    } while(choice7 != 0);

    break;
}

            case 8:
{
    showRecommendations(purchaseHistory,
                        products,
                        productCount);

    break;
}

         case 9:
{
    int customerChoice;

    do
    {
        printf("\n========================================\n");
        printf("         CUSTOMER MANAGEMENT\n");
        printf("========================================\n\n");

        printf("1. Add Customer\n");
        printf("2. Display Customers\n");
        printf("3. Search Customer\n");
        printf("4. Update Customer\n");
        printf("5. Delete Customer\n");
        printf("0. Back\n\n");

        printf("Enter your choice: ");
        scanf("%d", &customerChoice);

        switch(customerChoice)
        {
            case 1:
                addCustomer(customers, &customerCount);
                break;

            case 2:
                displayCustomers(customers, customerCount);
                break;

            case 3:
                searchCustomer(customers, customerCount);
                break;

            case 4:
                updateCustomer(customers, customerCount);
                break;

            case 5:
                deleteCustomer(customers, &customerCount);
                break;

            case 0:
                printf("\nReturning to main menu...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(customerChoice != 0);

    break;
}
                        case 10: 
                printf("\nBST Inorder Traversal: "); 
                inorderBST(root); 
                printf("\n"); 
                break; 

            case 11: 
            { 
                int updateId; 
                int found = 0; 

                printf("\nEnter Product ID to update: "); 
                scanf("%d", &updateId); 

                for(int i = 0; i < productCount; i++) 
                { 
                    if(products[i].id == updateId) 
                    { 
                        printf("\nEnter New Product Name: "); 
                        scanf("%s", products[i].name); 

                        printf("Enter New Category: "); 
                        scanf("%s", products[i].category); 

                        printf("Enter New Price: "); 
                        scanf("%f", &products[i].price); 

                        printf("Enter New Rating: "); 
                        scanf("%f", &products[i].rating); 

                        printf("Enter New Stock: "); 
                        scanf("%d", &products[i].stock); 

                        printf("\nProduct updated successfully!\n"); 

                        found = 1; 
                        break; 
                    } 
                } 

                if(found == 0) 
                { 
                    printf("\nProduct not found.\n"); 
                } 

                break; 
            } 

            case 12: 
            { 
                int deleteId; 
                int found = 0; 

                printf("\nEnter Product ID to delete: "); 
                scanf("%d", &deleteId); 

                for(int i = 0; i < productCount; i++) 
                { 
                    if(products[i].id == deleteId) 
                    { 
                        for(int j = i; j < productCount - 1; j++) 
                        { 
                            products[j] = products[j + 1]; 
                        } 

                        productCount--; 

                        root = deleteBST(root, deleteId); 

                        printf("\nProduct deleted successfully!\n"); 

                        found = 1; 
                        break; 
                    } 
                } 

                if(found == 0) 
                { 
                    printf("\nProduct not found.\n"); 
                } 

                break; 
            } 

            case 0:
                printf("\nThank you for using Smart E-Commerce System.\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(choice != 0);

    return 0;
}