# 이중 연결 리스트 (Doubly Linked List)

## 📌 개요
더미 헤드 노드(`org`)를 사용한 **이중 연결 리스트** 구현입니다.  
각 노드가 **선행 노드(prev)** 와 **후속 노드(next)** 를 모두 가리켜 양방향 탐색이 가능합니다.

---

## 🗂️ 파일 구조
```
📄 DbLinkedList.h   - 이중 연결 리스트 자료구조 및 연산 정의
📄 main.c           - 테스트 메인 코드 (사용 예시)
```

---

## 🔧 노드 구조

```c
typedef struct DNode {
    Element data;       // 데이터
    struct DNode* prev; // 선행 노드 포인터
    struct DNode* next; // 후속 노드 포인터
} DNode;
```

```
        ┌──────────────────────────────────────────┐
        │  org(더미)   노드0      노드1      노드2  │
        │  [  org  ] ↔ [ data ] ↔ [ data ] ↔ [ data ] → NULL
        │  prev=NULL   prev=org               next=NULL
        └──────────────────────────────────────────┘
```

---

## ⚙️ 제공 연산

| 함수 | 설명 | 시간복잡도 |
|------|------|-----------|
| `init_list()` | 리스트 초기화 | O(1) |
| `is_empty()` | 리스트가 비어있는지 확인 | O(1) |
| `is_full()` | 리스트가 가득 찼는지 확인 (항상 0) | O(1) |
| `size()` | 리스트의 노드 수 반환 | O(n) |
| `get_node(pos)` | pos번째 노드 포인터 반환 | O(n) |
| `get_entry(pos)` | pos번째 노드의 데이터 반환 | O(n) |
| `insert(pos, e)` | pos번째 위치에 데이터 삽입 | O(n) |
| `delete(pos)` | pos번째 노드 삭제 후 데이터 반환 | O(n) |
| `destroy_list()` | 리스트 전체 삭제 및 메모리 해제 | O(n) |

---

## 💡 단순 연결 리스트와의 차이점

| 비교 항목 | 단순 연결 리스트 | 이중 연결 리스트 |
|----------|---------------|---------------|
| 링크 방향 | 단방향 (next만) | 양방향 (prev + next) |
| 역방향 탐색 | ❌ 불가 | ✅ 가능 |
| 삭제 시 before 탐색 | 필요 | 불필요 (p->prev 활용) |
| 메모리 사용 | 적음 | 많음 (포인터 2개) |

---

## 📋 사용 예시

```c
#include <stdio.h>
#include <stdlib.h>
typedef int Element;
#include "DbLinkedList.h"

void main() {
    init_list();           // [        ]
    insert(0, 10);         // [ 10     ]
    insert(0, 20);         // [ 20, 10 ]
    insert(1, 30);         // [ 20, 30, 10 ]
    insert(size(), 40);    // [ 20, 30, 10, 40 ]

    delete(0);             // [ 30, 10, 40 ]
    delete(size() - 1);    // [ 30, 10 ]

    destroy_list();        // [        ]
}
```

---

## 📚 참고
- 최영규, **『쉽게 배우는 C자료구조』**, 생능출판사, 2024
