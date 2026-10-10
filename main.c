#include <stdio.h>
#include "models.h"
#include "console.h"
#include "catalog.h"
#include "browse.h"
#include "cart.h"
#include "orders.h"
#include "customer.h"
#include "recommend.h"

int main(void)
{
    /* All program state lives here and is handed to the modules. */
    Catalog      catalog   = { .count = 0 };
    Cart         cart      = { NULL };
    History      history   = { NULL, NULL };
    CustomerBook customers = { .count = 0 };

    static const char *const main_options[] = {
        "Add Product",
        "Display Products",
        "Search Products",
        "Sort Products",
        "Shopping Cart",
        "Purchase Products",
        "Purchase History",
        "Recommendations",
        "Customer Management",
        "Display BST (Inorder)",
        "Update Product",
        "Delete Product"
    };
    const int option_count = (int)(sizeof main_options / sizeof main_options[0]);

    int choice;
    while ((choice = console_menu("SMART E-COMMERCE SYSTEM", main_options,
                                  option_count, "Exit")) != 0) {
        switch (choice) {
            case 1:  catalog_ui_add(&catalog);                      break;
            case 2:  catalog_print_all(&catalog);                   break;
            case 3:  browse_search_menu(&catalog);                  break;
            case 4:  browse_sort_menu(&catalog);                    break;
            case 5:  cart_menu(&cart, &catalog);                    break;
            case 6:  orders_checkout(&cart, &history, &catalog);    break;
            case 7:  history_menu(&history, &catalog);              break;
            case 8:  recommend_show(&history, &catalog);            break;
            case 9:  customer_menu(&customers);                     break;
            case 10: catalog_ui_show_index(&catalog);               break;
            case 11: catalog_ui_update(&catalog);                   break;
            case 12: catalog_ui_remove(&catalog);                   break;
        }
    }

    printf("\nThank you for using Smart E-Commerce System.\n");

    cart_clear(&cart);
    history_destroy(&history);
    catalog_destroy(&catalog);
    return 0;
}
