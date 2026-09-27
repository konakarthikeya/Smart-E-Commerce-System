#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product
{
    int id;
    char name[50];
    char category[30];
    float price;
    float rating;
    int stock;
};

struct PurchaseNode
{
    int productId;
    struct PurchaseNode *next;
};

struct CartNode
{
    int productId;
    struct CartNode *next;
};

struct Customer
{
    int id;
    char name[50];
    char phone[20];
    char email[50];
};

struct BSTNode
{
    int productId;
    struct BSTNode *left;
    struct BSTNode *right;
};

struct BSTNode* insertBST(struct BSTNode *root, int productId)
{
    if(root == NULL)
    {
        struct BSTNode *newNode;

        newNode = (struct BSTNode *)malloc(sizeof(struct BSTNode));

        newNode->productId = productId;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if(productId < root->productId)
    {
        root->left = insertBST(root->left, productId);
    }
    else if(productId > root->productId)
    {
        root->right = insertBST(root->right, productId);
    }

    return root;
}

struct BSTNode* searchBST(struct BSTNode *root, int productId)
{
    if(root == NULL || root->productId == productId)
    {
        return root;
    }

    if(productId < root->productId)
    {
        return searchBST(root->left, productId);
    }

    return searchBST(root->right, productId);
}

void inorderBST(struct BSTNode *root)
{
    if(root != NULL)
    {
        inorderBST(root->left);

        printf("%d ", root->productId);

        inorderBST(root->right);
    }
}

struct BSTNode* deleteBST(struct BSTNode *root, int productId)
{
    if(root == NULL)
    {
        return root;
    }

    if(productId < root->productId)
    {
        root->left = deleteBST(root->left, productId);
    }
    else if(productId > root->productId)
    {
        root->right = deleteBST(root->right, productId);
    }
    else
    {
        if(root->left == NULL)
        {
            struct BSTNode *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            struct BSTNode *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            struct BSTNode *temp = root->right;

            while(temp->left != NULL)
            {
                temp = temp->left;
            }

            root->productId = temp->productId;

            root->right = deleteBST(root->right, temp->productId);
        }
    }

    return root;
}

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

        printf("Enter Product Name: ");
        scanf("%s", products[productCount].name);

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
                        printf("\nProduct %d\n", i + 1);
                        printf("ID       : %d\n", products[i].id);
                        printf("Name     : %s\n", products[i].name);
                        printf("Category : %s\n", products[i].category);
                        printf("Price    : %.2f\n", products[i].price);
                        printf("Rating   : %.1f\n", products[i].rating);
                        printf("Stock    : %d\n", products[i].stock);
                    }
                }

                break;

           case 3:
{
    int searchChoice;

    do
    {
        int searchId;
        char searchName[50];
        char searchCategory[30];
        int found;

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
                printf("\nEnter Product ID: ");
                scanf("%d", &searchId);

                found = 0;

                for(int i = 0; i < productCount; i++)
                {
                    if(products[i].id == searchId)
                    {
                        printf("\nProduct Found!\n");
                        printf("ID       : %d\n", products[i].id);
                        printf("Name     : %s\n", products[i].name);
                        printf("Category : %s\n", products[i].category);
                        printf("Price    : %.2f\n", products[i].price);
                        printf("Rating   : %.1f\n", products[i].rating);
                        printf("Stock    : %d\n", products[i].stock);

                        found = 1;
                        break;
                    }
                }

                if(found == 0)
                {
                    printf("\nProduct not found.\n");
                }

                break;


            case 2:
                printf("\nEnter Product Name: ");
                scanf("%s", searchName);

                found = 0;

                for(int i = 0; i < productCount; i++)
                {
                    if(strcmp(products[i].name, searchName) == 0)
                    {
                        printf("\nProduct Found!\n");
                        printf("ID       : %d\n", products[i].id);
                        printf("Name     : %s\n", products[i].name);
                        printf("Category : %s\n", products[i].category);
                        printf("Price    : %.2f\n", products[i].price);
                        printf("Rating   : %.1f\n", products[i].rating);
                        printf("Stock    : %d\n", products[i].stock);

                        found = 1;
                        break;
                    }
                }

                if(found == 0)
                {
                    printf("\nProduct not found.\n");
                }

                break;


            case 3:
                printf("\nEnter Category: ");
                scanf("%s", searchCategory);

                found = 0;

                for(int i = 0; i < productCount; i++)
                {
                    if(strcmp(products[i].category, searchCategory) == 0)
                    {
                        printf("\nProduct Found!\n");
                        printf("ID       : %d\n", products[i].id);
                        printf("Name     : %s\n", products[i].name);
                        printf("Category : %s\n", products[i].category);
                        printf("Price    : %.2f\n", products[i].price);
                        printf("Rating   : %.1f\n", products[i].rating);
                        printf("Stock    : %d\n", products[i].stock);

                        found = 1;
                    }
                }

                if(found == 0)
                {
                    printf("\nNo products found in this category.\n");
                }

                break;


            case 4:
            {
                struct BSTNode *result;

                printf("\nEnter Product ID: ");
                scanf("%d", &searchId);

                result = searchBST(root, searchId);

                if(result == NULL)
                {
                    printf("\nProduct not found.\n");
                }
                else
                {
                    for(int i = 0; i < productCount; i++)
                    {
                        if(products[i].id == result->productId)
                        {
                            printf("\nProduct Found using BST!\n");
                            printf("ID       : %d\n", products[i].id);
                            printf("Name     : %s\n", products[i].name);
                            printf("Category : %s\n", products[i].category);
                            printf("Price    : %.2f\n", products[i].price);
                            printf("Rating   : %.1f\n", products[i].rating);
                            printf("Stock    : %d\n", products[i].stock);
                            break;
                        }
                    }
                }

                break;
            }


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
    int i, j, minIndex;
    struct Product temp;

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
                for(i = 0; i < productCount - 1; i++)
                {
                    minIndex = i;

                    for(j = i + 1; j < productCount; j++)
                    {
                        if(products[j].price < products[minIndex].price)
                        {
                            minIndex = j;
                        }
                    }

                    if(minIndex != i)
                    {
                        temp = products[i];
                        products[i] = products[minIndex];
                        products[minIndex] = temp;
                    }
                }

                printf("\nProducts sorted by price successfully!\n");
                break;


            case 2:
                for(i = 0; i < productCount - 1; i++)
                {
                    minIndex = i;

                    for(j = i + 1; j < productCount; j++)
                    {
                        if(products[j].rating > products[minIndex].rating)
                        {
                            minIndex = j;
                        }
                    }

                    if(minIndex != i)
                    {
                        temp = products[i];
                        products[i] = products[minIndex];
                        products[minIndex] = temp;
                    }
                }

                printf("\nProducts sorted by rating successfully!\n");
                break;


            case 3:
                for(i = 0; i < productCount - 1; i++)
                {
                    minIndex = i;

                    for(j = i + 1; j < productCount; j++)
                    {
                        if(strcmp(products[j].name, products[minIndex].name) < 0)
                        {
                            minIndex = j;
                        }
                    }

                    if(minIndex != i)
                    {
                        temp = products[i];
                        products[i] = products[minIndex];
                        products[minIndex] = temp;
                    }
                }

                printf("\nProducts sorted by name successfully!\n");
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
                int productId;
                int found;
                int alreadyInCart;
                struct CartNode *newNode;
                struct CartNode *temp;

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
                            printf("\nEnter Product ID: ");
                            scanf("%d", &productId);

                            found = 0;
                            alreadyInCart = 0;

                            for(int i = 0; i < productCount; i++)
                            {
                                if(products[i].id == productId)
                                {
                                    found = 1;

                                    if(products[i].stock <= 0)
                                    {
                                        printf("\nProduct is out of stock!\n");
                                        break;
                                    }

                                    temp = cart;

                                    while(temp != NULL)
                                    {
                                        if(temp->productId == productId)
                                        {
                                            alreadyInCart = 1;
                                            break;
                                        }

                                        temp = temp->next;
                                    }

                                    if(alreadyInCart == 1)
                                    {
                                        printf("\nProduct is already in the cart!\n");
                                    }
                                    else
                                    {
                                        newNode = (struct CartNode *)malloc(sizeof(struct CartNode));

                                        newNode->productId = productId;
                                        newNode->next = cart;
                                        cart = newNode;

                                        printf("\nProduct added to cart successfully!\n");
                                    }

                                    break;
                                }
                            }

                            if(found == 0)
                            {
                                printf("\nProduct not found.\n");
                            }

                            break;

                        case 2:
                            if(cart == NULL)
                            {
                                printf("\nShopping cart is empty.\n");
                            }
                            else
                            {
                                printf("\n========================================\n");
                                printf("           SHOPPING CART\n");
                                printf("========================================\n");

                                temp = cart;

                                while(temp != NULL)
                                {
                                    printf("Product ID: %d\n", temp->productId);
                                    temp = temp->next;
                                }
                            }

                            break;

                        case 3:
                        {
                            int removeId;
                            int removeFound = 0;
                            struct CartNode *current = cart;
                            struct CartNode *prev = NULL;

                            printf("\nEnter Product ID to remove from cart: ");
                            scanf("%d", &removeId);

                            while(current != NULL)
                            {
                                if(current->productId == removeId)
                                {
                                    if(prev == NULL)
                                    {
                                        cart = current->next;
                                    }
                                    else
                                    {
                                        prev->next = current->next;
                                    }

                                    free(current);

                                    printf("\nProduct removed from cart!\n");

                                    removeFound = 1;
                                    break;
                                }

                                prev = current;
                                current = current->next;
                            }

                            if(removeFound == 0)
                            {
                                printf("\nProduct not found in cart.\n");
                            }

                            break;
                        }

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
                struct CartNode *temp = cart;
                struct CartNode *prev = NULL;

                if(cart == NULL)
                {
                    printf("\nCart is empty!\n");
                    break;
                }

                while(temp != NULL)
                {
                    int found = 0;

                    for(int i = 0; i < productCount; i++)
                    {
                        if(products[i].id == temp->productId)
                        {
                            found = 1;

                            if(products[i].stock > 0)
                            {
                                products[i].stock--;

                                struct PurchaseNode *newNode;

                                newNode = (struct PurchaseNode *)malloc(sizeof(struct PurchaseNode));

                                newNode->productId = temp->productId;
                                newNode->next = purchaseHistory;
                                purchaseHistory = newNode;

                                printf("\nProduct %d purchased successfully!\n",
                                       temp->productId);

                                if(prev == NULL)
                                {
                                    cart = temp->next;
                                    free(temp);
                                    temp = cart;
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
                                printf("\nProduct %d is out of stock!\n",
                                       temp->productId);

                                prev = temp;
                                temp = temp->next;
                            }

                            break;
                        }
                    }

                    if(found == 0)
                    {
                        printf("\nProduct no longer exists.\n");

                        if(prev == NULL)
                        {
                            cart = temp->next;
                            free(temp);
                            temp = cart;
                        }
                        else
                        {
                            prev->next = temp->next;
                            free(temp);
                            temp = prev->next;
                        }
                    }
                }

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
                        {
                            struct PurchaseNode *temp = purchaseHistory;

                            if(temp == NULL)
                            {
                                printf("\nPurchase history is empty.\n");
                            }
                            else
                            {
                                printf("\n===== PURCHASE HISTORY =====\n");

                                while(temp != NULL)
                                {
                                    printf("\nProduct ID: %d", temp->productId);

                                    for(int i = 0; i < productCount; i++)
                                    {
                                        if(products[i].id == temp->productId)
                                        {
                                            printf("\nName     : %s", products[i].name);
                                            printf("\nCategory : %s", products[i].category);
                                            printf("\nPrice    : %.2f", products[i].price);
                                            break;
                                        }
                                    }

                                    printf("\n");

                                    temp = temp->next;
                                }
                            }

                            break;
                        }

                        case 2:
                        {
                            int searchId;
                            int found = 0;
                            struct PurchaseNode *temp = purchaseHistory;

                            printf("\nEnter Product ID to search in purchase history: ");
                            scanf("%d", &searchId);

                            while(temp != NULL)
                            {
                                if(temp->productId == searchId)
                                {
                                    printf("\nProduct ID %d found in purchase history!\n",
                                           searchId);

                                    found = 1;
                                    break;
                                }

                                temp = temp->next;
                            }

                            if(found == 0)
                            {
                                printf("\nProduct not found in purchase history.\n");
                            }

                            break;
                        }

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
                struct PurchaseNode *temp = purchaseHistory;
                int shownIds[100];
                int shownCount = 0;

                if(temp == NULL)
                {
                    printf("\nNo purchase history available.\n");
                    break;
                }

                printf("\n===== RECOMMENDATIONS =====\n");

                while(temp != NULL)
                {
                    int purchasedId = temp->productId;
                    int purchasedIndex = -1;

                    for(int i = 0; i < productCount; i++)
                    {
                        if(products[i].id == purchasedId)
                        {
                            purchasedIndex = i;
                            break;
                        }
                    }

                    if(purchasedIndex != -1)
                    {
                        printf("\nBased on: %s\n",
                               products[purchasedIndex].name);

                        for(int i = 0; i < productCount; i++)
                        {
                            if(strcmp(products[i].category,
                                      products[purchasedIndex].category) == 0
                               && products[i].id != purchasedId
                               && products[i].stock > 0)
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
                                    printf("Recommended: %s (ID: %d)\n",
                                           products[i].name,
                                           products[i].id);

                                    shownIds[shownCount] = products[i].id;
                                    shownCount++;
                                }
                            }
                        }
                    }

                    temp = temp->next;
                }

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
                if(customerCount < 100)
                {
                    printf("\nEnter Customer ID: ");
                    scanf("%d", &customers[customerCount].id);

                    printf("Enter Customer Name: ");
                    scanf("%s", customers[customerCount].name);

                    printf("Enter Phone Number: ");
                    scanf("%s", customers[customerCount].phone);

                    printf("Enter Email: ");
                    scanf("%s", customers[customerCount].email);

                    customerCount++;

                    printf("\nCustomer added successfully!\n");
                }
                else
                {
                    printf("\nCustomer storage is full!\n");
                }

                break;


            case 2:
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

                break;


            case 3:
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

                break;
            }


          case 4:
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

    break;
}

            case 5:
            {
                int deleteId;
                int found = 0;

                printf("\nEnter Customer ID to delete: ");
                scanf("%d", &deleteId);

                for(int i = 0; i < customerCount; i++)
                {
                    if(customers[i].id == deleteId)
                    {
                        for(int j = i; j < customerCount - 1; j++)
                        {
                            customers[j] = customers[j + 1];
                        }

                        customerCount--;

                        printf("\nCustomer deleted successfully!\n");

                        found = 1;
                        break;
                    }
                }

                if(found == 0)
                {
                    printf("\nCustomer not found.\n");
                }

                break;
            }


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
