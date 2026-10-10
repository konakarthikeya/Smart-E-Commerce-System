#include <stdio.h>
#include <string.h>
#include "recommend.h"
#include "console.h"

/* Similarity tiers, strongest first. */
enum { TIER_BRAND_AND_TYPE, TIER_TYPE, TIER_CATEGORY, TIER_COUNT };

static bool tier_accepts(int tier, const Product *base, const Product *cand)
{
    switch (tier) {
        case TIER_BRAND_AND_TYPE:
            return strcmp(base->brand, cand->brand) == 0 &&
                   strcmp(base->type, cand->type) == 0;
        case TIER_TYPE:
            return strcmp(base->type, cand->type) == 0;
        default:
            return strcmp(base->category, cand->category) == 0;
    }
}

static void print_tier_heading(int tier, const Product *base)
{
    switch (tier) {
        case TIER_BRAND_AND_TYPE:
            printf("\nSame Brand and Type:\n");
            break;
        case TIER_TYPE:
            printf("\nOther %s Products:\n", base->type);
            break;
        default:
            printf("\nOther %s Products:\n", base->category);
            break;
    }
}

void recommend_show(const History *history, Catalog *cat)
{
    if (history->head == NULL) {
        printf("\nNo purchase history available.\n");
        return;
    }

    /* skip[i] is true when catalog item i must not be suggested:
       it was already bought, or it has already been suggested above. */
    bool skip[MAX_PRODUCTS] = { false };
    bool used_as_base[MAX_PRODUCTS] = { false };

    for (const Receipt *r = history->head; r != NULL; r = r->next) {
        int idx = catalog_index_of(cat, r->product_id);
        if (idx >= 0) {
            skip[idx] = true;
        }
    }

    console_banner("RECOMMENDATIONS");
    bool any_base = false;

    for (const Receipt *r = history->head; r != NULL; r = r->next) {
        int base_idx = catalog_index_of(cat, r->product_id);
        if (base_idx < 0 || used_as_base[base_idx]) {
            continue;                           /* deleted, or already handled */
        }
        used_as_base[base_idx] = true;
        any_base = true;

        const Product *base = &cat->items[base_idx];
        printf("\nBased on: %s %s\n", base->brand, base->name);

        for (int tier = 0; tier < TIER_COUNT; tier++) {
            int shown_here = 0;
            print_tier_heading(tier, base);

            for (int i = 0; i < cat->count; i++) {
                const Product *cand = &cat->items[i];
                if (skip[i] || cand->stock <= 0 || !tier_accepts(tier, base, cand)) {
                    continue;
                }
                printf("  %s %s (ID: %d)\n", cand->brand, cand->name, cand->id);
                skip[i] = true;
                shown_here++;
            }

            if (shown_here == 0) {
                printf("  No products available.\n");
            }
        }
    }

    if (!any_base) {
        printf("\nThe products you bought are no longer listed.\n");
    }
}
