#include <stdio.h>

int main() {
    int wordCount = 0;
    int inWord = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (inWord == 1) {
                inWord = 0;
            }
        } else {
            if (inWord == 0) {
                wordCount++;
                inWord = 1;
            }
        }
    }

    // Check if the last character was part of a word
    if (inWord == 1) {
        wordCount++;
    }

    printf("\nNumero parole: %d\n", wordCount);
    return 0;
}