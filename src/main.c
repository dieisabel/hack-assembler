#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io/io.h"

int main(int argc, char const *argv[]) {
    char *file_content = read_file_content("data/Add.asm");

    // Assembler

    // Determine amount of instructions
    int lines = 0;
    for (int i = 0; file_content[i] != '\0'; i++) {
        if (file_content[i] == '\n') {
            lines++;
        }
    }

    // Parse instructions into array
    char *instructions[lines];
    char *token = strtok(file_content, "\n");
    int counter = 0;
    while (token != NULL) {
        instructions[counter] = token;
        token = strtok(NULL, "\n");
        counter++;
    }

    // Parse instructions
    char *instruction;
    for (int i = 0; i < lines; i++) {
        instruction = instructions[i];

        // Determine is this is A instruction or C instruction
        if (instruction[0] == '@') {
            // Get value
            // Dont count \n and first @ symbol
            int value_length = strlen(instruction) - 1 - 1;
            char string_value[value_length + 1];
            for (int i = 0; i < value_length; i++) {
                string_value[i] = instruction[1 + i];
            }
            string_value[value_length + 1] = '\0';

            // TODO: We need to check if number is bigger than 15 bit
            int value = (int) strtol(string_value, NULL, 10);

            int output_instruction = 0b0000000000000000;
            output_instruction |= value;
        }
    }

    free(file_content);
    return EXIT_SUCCESS;
}
