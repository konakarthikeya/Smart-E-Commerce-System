#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Product
{
    int id;
    char brand[30];
    char name[50];
    char type[30];
    char category[30];
    float price;
    float rating;
    int stock;
};
struct CartNode
{
    int productId;
    int quantity;
    struct CartNode *next;
};

struct PurchaseNode
{
    int productId;
    int quantity;
    float amountPaid;
    struct PurchaseNode *next;
};

struct Customer
{
    int id;
    char name[50];
    char phone[20];
    char email[50];
};

#endif