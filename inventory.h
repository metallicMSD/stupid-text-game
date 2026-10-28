#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 20

typedef enum {
    ITEM_WEAPON,
    ITEM_HEALTH_POTION,
    ITEM_MANA_POTION
} ItemType;

typedef struct {
    char name[32];
    char description[96];
    ItemType type;
    int value;          //heal amount, mana amount, damage, etc.
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int count;          //slots in use
} Inventory;

static void inventory_init(Inventory *inv) {
    inv->count = 0;
}

//1 is success, else is full 
static int add_item(Inventory *inv, const char *name, const char *desc,
                    ItemType type, int value) {
    if (inv->count >= MAX_ITEMS) {
        return 0;
    }
    Item *it = &inv->items[inv->count];
    strncpy(it->name, name, sizeof(it->name) - 1);
    it->name[sizeof(it->name) - 1] = '\0';
    strncpy(it->description, desc, sizeof(it->description) - 1);
    it->description[sizeof(it->description) - 1] = '\0';
    it->type = type;
    it->value = value;
    inv->count++;
    return 1;
}

static void remove_item(Inventory *inv, int index) {
    for (int i = index; i < inv->count - 1; i++) {
        inv->items[i] = inv->items[i + 1];
    }
    inv->count--;
}

static void show_inventory(const Inventory *inv) {
    printf("\n--- INVENTORY (%d/%d) ---\n", inv->count, MAX_ITEMS);
    if (inv->count == 0) {
        printf("(empty)\n");
        return;
    }
    for (int i = 0; i < inv->count; i++) {
        printf("%d. %s\n", i + 1, inv->items[i].name);
    }
}

static void use_item(Inventory *inv, int index, int *health, int *mana) {
    Item *it = &inv->items[index];

    switch (it->type) {
        case ITEM_HEALTH_POTION:
            *health += it->value;
            printf("YOU RESTORE %d HEALTH. HEALTH: %d\n", it->value, *health);
            remove_item(inv, index);    // 'it' is stale after this
            break;
        case ITEM_MANA_POTION:
            *mana += it->value;
            printf("YOU RESTORE %d MANA. MANA: %d\n", it->value, *mana);
            remove_item(inv, index);
            break;
        case ITEM_WEAPON:
            printf("NOW IS NOT THE TIME\n");
            break;
    }
}

static void inventory_menu(Inventory *inv, int *health, int *mana) {
    while (1) {
        show_inventory(inv);
        if (inv->count == 0) return;

        printf("SELECT AN ITEM (0 TO GO BACK): ");
        int sel;
        if (scanf("%d", &sel) != 1) {
            while (getchar() != '\n');
            continue;
        }
        if (sel == 0) return;
        if (sel < 1 || sel > inv->count) {
            printf("INVALID ITEM\n");
            continue;
        }
        int index = sel - 1;

        printf("1. INSPECT  2. USE  3. THROW AWAY  4. BACK: ");
        int action;
        if (scanf("%d", &action) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (action) {
            case 1:
                printf("%s: %s\n", inv->items[index].name,
                       inv->items[index].description);
                break;
            case 2:
                use_item(inv, index, health, mana);
                break;
            case 3:
                printf("YOU THREW AWAY %s.\n", inv->items[index].name);
                remove_item(inv, index);
                break;
            default:
                break;
        }
    }
}

#endif
