#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "customer.h"
#include "console.h"

static int index_of(const CustomerBook *book, int id)
{
    for (int i = 0; i < book->count; i++) {
        if (book->items[i].id == id) {
            return i;
        }
    }
    return -1;
}

static void print_customer(const Customer *c)
{
    printf("ID    : %d\n", c->id);
    printf("Name  : %s\n", c->name);
    printf("Phone : %s\n", c->phone);
    printf("Email : %s\n", c->email);
}

/* Name, phone and email are the editable fields. */
static void read_contact_details(Customer *c)
{
    console_text("Enter Customer Name: ", c->name,  sizeof c->name);
    console_text("Enter Phone Number: ",  c->phone, sizeof c->phone);
    console_text("Enter Email: ",         c->email, sizeof c->email);
}

static void ui_add(CustomerBook *book)
{
    if (book->count >= MAX_CUSTOMERS) {
        printf("\nCustomer storage is full!\n");
        return;
    }

    Customer c;
    for (;;) {
        c.id = console_int("\nEnter Customer ID: ", 1, INT_MAX);
        if (index_of(book, c.id) < 0) {
            break;
        }
        printf("Customer ID already exists. Please enter a different one.\n");
    }

    read_contact_details(&c);
    book->items[book->count++] = c;
    printf("\nCustomer added successfully!\n");
}

static void ui_display(const CustomerBook *book)
{
    if (book->count == 0) {
        printf("\nNo customers available.\n");
        return;
    }

    console_banner("CUSTOMER LIST");
    for (int i = 0; i < book->count; i++) {
        printf("\nCustomer %d\n", i + 1);
        print_customer(&book->items[i]);
    }
}

static void ui_search(const CustomerBook *book)
{
    int id = console_int("\nEnter Customer ID: ", 1, INT_MAX);
    int idx = index_of(book, id);

    if (idx < 0) {
        printf("\nCustomer not found.\n");
        return;
    }
    printf("\nCustomer Found!\n");
    print_customer(&book->items[idx]);
}

static void ui_update(CustomerBook *book)
{
    int id = console_int("\nEnter Customer ID to update: ", 1, INT_MAX);
    int idx = index_of(book, id);

    if (idx < 0) {
        printf("\nCustomer not found.\n");
        return;
    }

    printf("\nCurrent Customer Details\n----------------------------\n");
    print_customer(&book->items[idx]);

    printf("\n");
    read_contact_details(&book->items[idx]);

    printf("\nCustomer updated successfully!\n");
    printf("\nUpdated Customer Details\n----------------------------\n");
    print_customer(&book->items[idx]);
}

static void ui_delete(CustomerBook *book)
{
    int id = console_int("\nEnter Customer ID to delete: ", 1, INT_MAX);
    int idx = index_of(book, id);

    if (idx < 0) {
        printf("\nCustomer not found.\n");
        return;
    }

    int tail = book->count - idx - 1;
    memmove(&book->items[idx], &book->items[idx + 1], (size_t)tail * sizeof(Customer));
    book->count--;
    printf("\nCustomer deleted successfully!\n");
}

void customer_menu(CustomerBook *book)
{
    static const char *const options[] = {
        "Add Customer",
        "Display Customers",
        "Search Customer",
        "Update Customer",
        "Delete Customer"
    };

    int choice;
    while ((choice = console_menu("CUSTOMER MANAGEMENT", options, 5, "Back")) != 0) {
        switch (choice) {
            case 1: ui_add(book);     break;
            case 2: ui_display(book); break;
            case 3: ui_search(book);  break;
            case 4: ui_update(book);  break;
            case 5: ui_delete(book);  break;
        }
    }
}
