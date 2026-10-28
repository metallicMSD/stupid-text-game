#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "inventory.h"
#include "venture.h"
#include "textbox.h"

typedef enum {
    WIZARD = 1,
    KNIGHT,
    ARCHER
} ClassType;

typedef struct {
    ClassType class_id;
    int health;
    int mana;
    Inventory inv;
} Player;

typedef struct {
    int choice1;
    int choice2;
    int choice3;
    int choice4;
    int choice5;
} Choice;

void textbox(const char *text);

int main() {
    Player player;
    Choice choice;

    inventory_init(&player.inv);

    printf("OPEN WORLD TEXT BASED ADVENTURE GAME!\n");

    sleep(3);

    printf("CHOOSE YOUR CLASS!\n");
    printf("1. WIZARD\n2. KNIGHT\n3. ARCHER\n");
    
    scanf("%d", (int *)&player.class_id);

    switch (player.class_id) {
        case WIZARD:
            player.health = 80;
            player.mana = 100;
            add_item(&player.inv, "WOOD STAFF", "A boring old stick you found.", ITEM_WEAPON, 12);
            add_item(&player.inv, "MANA POTION", "Restores 30 mana.", ITEM_MANA_POTION, 30);
            printf("YOU ARE A WIZARD\n");
            sleep(1);
            printf("YOU HAVE %d HEALTH AND %d MANA\n", player.health, player.mana);
            break;
        case KNIGHT:
            player.health = 150;
            player.mana = 20;
            add_item(&player.inv, "SWORD", "Trusty metal sword.", ITEM_WEAPON, 22);
            add_item(&player.inv, "HEALTH POTION", "Restores 40 health.", ITEM_HEALTH_POTION, 40);
            printf("YOU ARE A KNIGHT\n");
            sleep(1);
            printf("YOU HAVE %d HEALTH AND %d MANA\n", player.health, player.mana);
            break;
        case ARCHER:
            player.health = 100;
            player.mana = 50;
            add_item(&player.inv, "BOW", "Old bow.", ITEM_WEAPON, 17);
            printf("YOU ARE AN ARCHER\n");
            sleep(1);
            printf("YOU HAVE %d HEALTH AND %d MANA\n", player.health, player.mana);
            break;
        default:
            printf("INVALID CLASS\n");
            return 1;
    }

    sleep(2);
    
    //main loop 
    while (1) {
        textbox("WELL. YOU ARE A FREE MAN, WHAT WOULD YOU LIKE TO DO? 1.INFO 2.ROAM 3.INVENTORY");
    
        printf("I choose:... ");
        if (scanf("%d", &choice.choice1) != 1) {
            choice.choice1 = 0;
            while (getchar() != '\n'); //clear invalid input
        }

        switch (choice.choice1) {
            case 1:
                printf("YOU HAVE %d HEALTH AND %d MANA.\n", player.health, player.mana);
                while (getchar() != '\n'); //clear input buffer
                
                printf("\n[Press Enter to continue]");
                getchar(); //pause
                break;

            case 2:
                venture();
                break;

            case 3:
                inventory_menu(&player.inv, &player.health, &player.mana);
                break;
                
            default:
                printf("INVALID CHOICE\n");
                while (getchar() != '\n'); 
                break;
        }
        
    }

    return 0;
} 
