#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "inventory.h"
#include "textbox.h"
#include "choice.h"

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


int venture();
int town();
int town_talk();
void textbox(const char *text);

int main() {
    Player player;
    int player_choice;

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

    player_choice = get_choice(1, 3);
    
switch (player_choice) {
            case 1:
                printf("YOU HAVE %d HEALTH AND %d MANA.\n", player.health, player.mana);
                printf("\n[Press Enter to continue]");
                getchar(); // pause
                break;

            case 2:
                venture();
                break;

            case 3:
                inventory_menu(&player.inv, &player.health, &player.mana);
                break;
                
            default:
                break;
        }
    }

    return 0;
} 

int venture() {

    printf("\nWHERE DO YOU WANT TO ROAM?\n");
    printf("1. TOWN\n");
    printf("2. WOODS\n");
    printf("3. CASTLE\n");

    int location_choice = get_choice(1, 3);

    switch (location_choice) {
        case 1:
            textbox("OFF TO THE TOWN, SOMEONE LIKE YOU HAS NO USE FOR MONEY, THIS PLACE IS QUITE BORING.");
            sleep(2);
            town();
            break;
        case 2:
            textbox("NOTHING BETTER TO DO, OFF TO THE WOODS.");
            sleep(2);
            break;
        case 3:
            textbox("\"I HATE THE DRAGON HERE\" YOU SAY, YOU MUST END HIM");
            sleep(2);
            break;
        default:
            break;
    }
return 0;
}

int town(){

  textbox("THIS PLACE KIND OF SUCKS");
  sleep(2);

while (1) {
        textbox("WHAT DO YOU WANT TO DO HERE? 1.TALK 2.LEAVE");
        int activity_choice = get_choice(1, 2);

        switch (activity_choice) {
            case 1:
                textbox("WHO DO YOU WANT TO TALK TO? 1.commoner 2.shopkeeper 3.town knight");
                // town_talk();
                break;

            case 2:
                textbox("You leave the town.");
                sleep(1);
                return 0;
        }
    }
}
