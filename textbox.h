#include <stdio.h>
#include <string.h>
// Textbox function with automatic word wrapping
void textbox(const char *text) {
    int max_width = 40; // Max characters allowed per line inside the box
    int len = strlen(text);
    int current_index = 0;

    printf("********************************************\n");
    printf("*                                          *\n");

    // Print text line by line, wrapping if it's too long
    while (current_index < len) {
        int chunk_size = max_width;
        
        // If the remaining text is longer than max_width, find a space to wrap cleanly
        if (current_index + chunk_size < len) {
            int break_point = chunk_size;
            while (break_point > 0 && text[current_index + break_point] != ' ') {
                break_point--;
            }
            if (break_point > 0) {
                chunk_size = break_point; // Wrap at the space
            }
        } else {
            chunk_size = len - current_index;
        }

        // Print the formatted line padded to fit the 42-character width box
        printf("* %-40.40s *\n", &text[current_index]);
        
        current_index += chunk_size;
        // Skip leading space after wrap point
        if (current_index < len && text[current_index] == ' ') {
            current_index++;
        }
    }

    printf("*                                          *\n");
    printf("********************************************\n");
}
