#include "kvs.h"

kvs_t* open() {
    kvs_t* kvs = (kvs_t*)malloc(sizeof(kvs_t));
    if (!kvs) return NULL;
    
    kvs->level = 0;
    kvs->items = 0;

    // 헤더 노드 초기화
    kvs->header = (node_t*)malloc(sizeof(node_t));
    if (!kvs->header) {
        free(kvs);
        return NULL;
    }
    kvs->header->forward = (node_t**)malloc(sizeof(node_t*) * (MAX_LEVEL + 1));
    for (int i = 0; i <= MAX_LEVEL; i++) {
        kvs->header->forward[i] = NULL;
    }
    return kvs;
}
