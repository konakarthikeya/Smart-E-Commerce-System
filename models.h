#ifndef MODELS_H
#define MODELS_H

/* Capacity limits shared by every module. */
#define MAX_PRODUCTS  100
#define MAX_CUSTOMERS 100

typedef struct {
    int   id;
    char  brand[30];
    char  name[50];
    char  type[30];
    char  category[30];
    float price;
    float rating;      /* 0.0 - 5.0 */
    int   stock;
} Product;

/* One line in the shopping cart (singly linked list). */
typedef struct CartItem {
    int product_id;
    int quantity;
    struct CartItem *next;
} CartItem;

/* One completed purchase line (singly linked list). */
typedef struct Receipt {
    int   product_id;
    int   quantity;
    float amount_paid;
    struct Receipt *next;
} Receipt;

typedef struct {
    int  id;
    char name[50];
    char phone[20];
    char email[50];
} Customer;

#endif
