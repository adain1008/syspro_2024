#include "kvs.h"

int close(kvs_t* kvs) {
    node_t* current = kvs->header->forward[0];
    while (current != NULL) {
        node_t* temp = current;
        current = current->forward[0];
        free(temp->value);
        free(temp->forward);
        free(temp);
    }
    free(kvs->header->forward);
    free(kvs->header);
    free(kvs);
    return 0;
}
