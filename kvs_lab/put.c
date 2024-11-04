#include "kvs.h"

// 랜덤 레벨 생성 함수
static int randomLevel() {
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

int put(kvs_t* kvs, const char* key, const char* value) {
    node_t* update[MAX_LEVEL + 1];
    node_t* current = kvs->header;

    // 삽입 위치 찾기
    for (int i = kvs->level; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    // 키가 존재하면 업데이트
    if (current != NULL && strcmp(current->key, key) == 0) {
        free(current->value);
        current->value = strdup(value);
        return 0;
    }

    // 새로운 노드 생성 및 삽입
    int level = randomLevel();
    if (level > kvs->level) {
        for (int i = kvs->level + 1; i <= level; i++) {
            update[i] = kvs->header;
        }
        kvs->level = level;
    }

    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    strcpy(newNode->key, key);
    newNode->value = strdup(value);
    newNode->forward = (node_t**)malloc(sizeof(node_t*) * (level + 1));
    newNode->level = level;

    for (int i = 0; i <= level; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
    kvs->items++;
    return 0;
}
