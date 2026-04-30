# 🔗 LinkedList — 연결 리스트 (C언어)
---

## 📌 개요

단순 연결 리스트(Singly Linked List)를 C언어로 직접 구현한 코드입니다.  
배열 리스트와 달리 **동적 메모리 할당**을 사용하므로 크기 제한이 없으며,  
포인터로 노드를 연결하는 연결 구조의 핵심 원리를 익힐 수 있습니다.

---

## 🔧 제공 연산

### 기본 연산

| 함수 | 설명 |
|------|------|
| `init_list()` | 리스트 초기화 (`head = NULL`) |
| `is_empty()` | 리스트가 비어 있으면 1, 아니면 0 반환 |
| `is_full()` | 항상 0 반환 (동적 할당이므로 한계 없음) |
| `insert(pos, e)` | `pos` 위치에 요소 `e` 삽입 |
| `delete(pos)` | `pos` 위치의 노드 삭제 후 요소 반환 |
| `get_entry(pos)` | `pos` 위치의 요소 반환 (삭제 없음) |
| `destroy_list()` | 리스트 전체 삭제 및 메모리 해제 |
| `size()` | 현재 노드 수 반환 |

### 추가 연산

| 함수 | 설명 |
|------|------|
| `append(e)` | 리스트 맨 끝에 요소 추가 |
| `pop()` | 리스트 맨 끝 요소 삭제 후 반환 |
| `replace(pos, e)` | `pos` 위치의 요소를 `e`로 교체 |
| `find(e)` | 요소 `e`의 위치(인덱스) 반환, 없으면 -1 |

---

## 💡 핵심 동작 원리

### 삽입 — `insert(pos, e)`

**① 맨 앞(pos = 0) 삽입**

새 노드의 link를 기존 head로 연결하고, head를 새 노드로 교체합니다.

```
삽입 전:  head ──► [10│●]──►[20│NULL]

새 노드:  [99│●]

삽입 후:  head ──► [99│●]──►[10│●]──►[20│NULL]
```

**② 중간 / 끝(pos > 0) 삽입**

`pos-1` 위치의 노드(before)를 찾아 포인터를 재연결합니다.

```
pos=1에 99 삽입:

[before]       [새 노드]
[10│●]──►      [99│●]
     │               │
     └──► [20│NULL]  │
                     │
재연결 후:           ▼
[10│●]──►[99│●]──►[20│NULL]
```

### 삭제 — `delete(pos)`

삭제할 노드(p)의 이전 노드(before)의 link를 p->link로 연결하고, p를 해제합니다.

```
pos=1 삭제 (노드 20 삭제):

[before]   [p: 삭제]
[10│●]──►[20│●]──►[30│NULL]

재연결 후:
[10│●]──────────►[30│NULL]
        (20 해제)
```

---

## 🖥️ 사용 예시

```c
#include <stdio.h>
#include <stdlib.h>

typedef int Element;
#include "LinkedList.h"

int main() {
    init_list();

    append(10);
    append(20);
    append(30);
    insert(1, 99);   // [10, 99, 20, 30]

    printf("size    : %d\n", size());           // 4
    printf("pos 1   : %d\n", get_entry(1));     // 99
    printf("find 20 : %d\n", find(20));         // 2

    delete(1);                                  // [10, 20, 30]
    printf("pop     : %d\n", pop());            // 30

    replace(0, 50);                             // [50, 20]
    printf("pos 0   : %d\n", get_entry(0));     // 50

    destroy_list();
    printf("empty   : %d\n", is_empty());       // 1

    return 0;
}
```

**출력 결과**

```
size    : 4
pos 1   : 99
find 20 : 2
pop     : 30
pos 0   : 50
empty   : 1
```

---

## 🔄 배열 리스트(ArrayList)와 비교

| 항목 | 배열 리스트 | 연결 리스트 |
|------|:-----------:|:-----------:|
| 크기 제한 | 있음 (MAX_SIZE) | 없음 (동적 할당) |
| 임의 접근 | O(1) | O(n) |
| 삽입 / 삭제 | O(n) — 요소 이동 필요 | O(n) — 탐색 후 포인터 재연결 |
| 맨 앞 삽입 / 삭제 | O(n) | O(1) |
| 메모리 구조 | 연속 공간 | 불연속 공간 |
| 메모리 해제 | 불필요 | `destroy_list()` 필수 |

---

## 📚 참고

- 교재: 쉽게 배우는 C자료구조, 최영규, 생능출판사 (2024)
- 참고 파일: `ch06/LinkedList.h`
