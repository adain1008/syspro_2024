#ifndef KVS_H
#define KVS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEVEL 4  // 스킵 리스트의 최대 레벨 정의

// 스킵 리스트의 개별 노드를 나타내는 구조체
typedef struct node {
    char key[100];           // 키
    char* value;             // 값 (동적 할당)
    struct node** forward;   // 여러 레벨에서 다음 노드를 가리키는 포인터 배열
    int level;               // 노드가 가지는 레벨 수
} node_t;

// KVS 구조체 (스킵 리스트 자체를 관리)
typedef struct kvs {
    node_t* header;          // 스킵 리스트의 헤더 노드
    int level;               // 현재 스킵 리스트의 최대 레벨
    int items;               // 저장된 데이터의 개수
} kvs_t;

// 함수 프로토타입 선언
kvs_t* open();                       // KVS 초기화
int close(kvs_t* kvs);               // 모든 메모리 해제 후 KVS 닫기
int put(kvs_t* kvs, const char* key, const char* value); // KVS에 키-값 삽입
char* get(kvs_t* kvs, const char* key);                  // KVS에서 키로 값 검색

#endif // KVS_H

