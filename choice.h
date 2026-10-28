#ifndef CHOICE_H
#define CHOICE_H

#include <stdio.h>

int get_choice(int min, int max) {
    int choice;
    
    while (1) {
        printf("I choose: ... ");
      
        if (scanf("%d", &choice) != 1) {
            printf("NOT A CHOICE!\n");
            while (getchar() != '\n');
            continue;
        }
        
        while (getchar() != '\n');

        if (choice >= min && choice <= max) {
            return choice;
        } else {
            printf("INVALID CHOICE.\n");
        }
    }
}

#endif
