#include "kvs.h"
#include <stdio.h>
#include <string.h>

int main() {
    kvs_t* kvs = open();
    if (!kvs) {
        printf("Failed to open kvs\n");
        return -1;
    }

    FILE* query_file = fopen("query.dat", "r");
    FILE* answer_file = fopen("answer.dat", "w");
    if (!query_file || !answer_file) {
        printf("Failed to open query or answer file\n");
        close(kvs);
        return -1;
    }

    char command[10];
    char key[100];
    char value[100];

    while (fscanf(query_file, "%[^,],%[^,],%s\n", command, key, value) != EOF) {
        if (strcmp(command, "get") == 0) {
            char* result = get(kvs, key);
            if (result) {
                fprintf(answer_file, "%s\n", result);  // value 값만 출력
            } else {
                fprintf(answer_file, "-1\n");
            }
        } else if (strcmp(command, "set") == 0) {
            put(kvs, key, value);
        }
    }

    fclose(query_file);
    fclose(answer_file);
    close(kvs);

    return 0;
}
