#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

void count_characters(FILE *file) {
    int count = 0;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        count += strlen(buffer);
    }

    printf("Character count: %d\n", count);
}

void count_words(FILE *file) {
    int count = 0;
    char buffer[BUFFER_SIZE];
    int in_word = 0;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (isspace(buffer[i]) || buffer[i] == ',') {
                if (in_word) {
                    count++;
                    in_word = 0;
                }
            } else {
                in_word = 1;
            }
        }
    }

    // 如果文件末尾在一个单词中，确保最后一个单词也被计数
    if (in_word) {
        count++;
    }

    printf("Word count: %d\n", count);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <-c|-w>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *mode = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    if (strcmp(mode, "-c") == 0) {
        count_characters(file);
    } else if (strcmp(mode, "-w") == 0) {
        count_words(file);
    } else {
        fprintf(stderr, "Invalid mode: %s. Use -c for character count or -w for word count.\n", mode);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
