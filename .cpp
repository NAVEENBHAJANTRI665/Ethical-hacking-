#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_STRINGS 10
#define MAX_LEN 100

typedef struct {
    char strings[NUM_STRINGS][MAX_LEN];
    char original[NUM_STRINGS][MAX_LEN];
    int swapCount;
} StringState;

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main() {
    StringState state;
    state.swapCount = 0;

    const char *filename = "strings.txt";
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Error: strings.txt not found\n");
        return 1;
    }

    int count = 0;
    while (count < NUM_STRINGS && fgets(state.strings[count], MAX_LEN, file)) {
        state.strings[count][strcspn(state.strings[count], "\n")] = '\0';
        strcpy(state.original[count], state.strings[count]);
        count++;
    }
    fclose(file);

    if (count < NUM_STRINGS) {
        printf("Need at least 10 strings\n");
        return 1;
    }

    // reverse all strings
    for (int i = 0; i < NUM_STRINGS; i++) {
        reverseString(state.strings[i]);
    }

    // FIXED swaps (no randomness)
    int fixedSwaps = 7;

    for (int s = 0; s < fixedSwaps; s++) {
        int i = s % NUM_STRINGS;
        int j = (s + 1) % NUM_STRINGS;

        int len1 = strlen(state.strings[i]);
        int len2 = strlen(state.strings[j]);

        if (len1 > 0 && len2 > 0) {
            char temp = state.strings[i][0];
            state.strings[i][0] = state.strings[j][0];
            state.strings[j][0] = temp;

            state.swapCount++;
        }
    }

    printf("\n--- Strings ---\n");
    for (int i = 0; i < NUM_STRINGS; i++) {
        printf("%s\n", state.strings[i]);
    }

    printf("\nCorrect answer (swap count): %d\n", state.swapCount);

    return 0;
}
