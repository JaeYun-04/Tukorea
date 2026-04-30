#include <stdio.h>
#include <stdlib.h>

typedef int Element;

// 자기참조 구조체
typedef struct Node {
    Element data;
    struct Node* link;
} Node;

// 더미 헤드 노드 (head 역할)
// org.link가 실제 첫 번째 노드를 가리킴
Node org = {0, NULL};

// ----------------------------------------------------------------
// 노드 동적 할당 / 해제
// ----------------------------------------------------------------
Node* alloc_node(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->link = NULL;
    return p;
}

Element free_node(Node* p)
{
    Element e = p->data;
    free(p);
    return e;
}

void error(char* str)
{
    printf("%s\n", str);
    exit(1);
}

// ----------------------------------------------------------------
// 기본 리스트 연산
// ----------------------------------------------------------------
int is_empty()
{
    return org.link == NULL;
}

int is_full()
{
    return 0;
}

void init_list()
{
    // 더미 노드만 남기고 초기화
    org.link = NULL;
}

// ----------------------------------------------------------------
// 노드/데이터 접근
// ----------------------------------------------------------------

// pos번째 실제 노드 반환
// org는 -1번 노드, org.link는 0번 노드로 간주
Node* get_node(int pos)
{
    if (pos < -1) {
        return NULL;
    }
    // pos == -1이면 더미 노드 org 반환 (삽입/삭제에서 before로 활용)
    Node* p = &org;
    for (int i = -1; i < pos; i++) {
        p = p->link;
        if (p == NULL) {
            return NULL;
        }
    }
    return p;
}

Element get_entry(int pos)
{
    Node* p = get_node(pos);
    if (p == NULL) {
        error("Invalid Position Error!");
    }
    return p->data;
}

// ----------------------------------------------------------------
// 삽입 연산
// ----------------------------------------------------------------
// before = get_node(pos - 1) 이 pos==0이면 더미노드 &org를 반환하므로
// 항상 before != NULL → 분기 불필요!
void insert(int pos, Element e)
{
    Node* before = get_node(pos - 1); // pos==0 → &org 반환
    if (before == NULL) {
        error("Invalid Position Error!");
    }
    Node* p = alloc_node(e);
    p->link = before->link;
    before->link = p;
}

// ----------------------------------------------------------------
// 삭제 연산
// ----------------------------------------------------------------
Element delete(int pos)
{
    if (is_empty()) {
        error("Underflow Error!");
    }
    Node* before = get_node(pos - 1); // pos==0 → &org 반환
    if (before == NULL || before->link == NULL) {
        error("Invalid Position Error!");
    }
    Node* p = before->link;   // 삭제할 노드
    before->link = p->link;   // before → p 다음 노드로 연결
    return free_node(p);
}

// ----------------------------------------------------------------
// 리스트 전체 삭제
// ----------------------------------------------------------------
void destroy_list()
{
    while (!is_empty()) {
        delete(0);
    }
}

// ----------------------------------------------------------------
// 크기
// ----------------------------------------------------------------
int size()
{
    int count = 0;
    for (Node* p = org.link; p != NULL; p = p->link) {
        count++;
    }
    return count;
}

// ----------------------------------------------------------------
// 추가 연산 (코드 6.6)
// ----------------------------------------------------------------

// 맨 뒤에 삽입
void append(Element e)
{
    Node* p = alloc_node(e);
    // tail 탐색: org부터 시작
    Node* tail = &org;
    while (tail->link != NULL) {
        tail = tail->link;
    }
    tail->link = p;
}

// 맨 뒤 노드 삭제 후 반환
Element pop()
{
    if (is_empty()) {
        error("Underflow Error!");
    }
    Node* before = &org;
    Node* p = org.link;
    while (p->link != NULL) {
        before = p;
        p = p->link;
    }
    before->link = NULL;
    return free_node(p);
}

// pos번째 데이터 교체
void replace(int pos, Element e)
{
    Node* p = get_node(pos);
    if (p == NULL) {
        error("Invalid Position Error!");
    }
    p->data = e;
}

// 데이터 e의 위치 반환 (없으면 -1)
int find(Element e)
{
    int i = 0;
    for (Node* p = org.link; p != NULL; p = p->link, i++) {
        if (p->data == e) {
            return i;
        }
    }
    return -1;
}

// ----------------------------------------------------------------
