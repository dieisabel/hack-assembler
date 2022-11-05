#include "io/io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long get_filestream_length(FILE *filestream);

char *read_file_content(char *filepath) {
    FILE *filestream = fopen(filepath, "r");
    // TODO: process error
    if (filestream == NULL) {
        return NULL;
    }
    long filesize = get_filestream_length(filestream);
    char *buffer = (char*) malloc(sizeof(char) * filesize + 1);
    // TDDO: process error
    if (buffer == NULL) {
        return NULL;
    }
    fread(buffer, sizeof(char), filesize, filestream);
    buffer[filesize] = '\0';
    fclose(filestream);
    return buffer;
}

// TODO: what is file is empty?
static long get_filestream_length(FILE *filestream) {
    fseek(filestream, 0, SEEK_END);
    long filesize = ftell(filestream);
    fseek(filestream, 0, SEEK_SET);
    return filesize;
}
