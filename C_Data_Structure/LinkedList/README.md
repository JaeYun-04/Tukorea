# 🔗 단일 연결 리스트 (Singly Linked List)

> 더미 헤드 노드(dummy head node) 방식으로 구현한 C언어 단일 연결 리스트입니다.

---

## 🏗️ 구조

```
org (더미 헤드)  →  [0번 노드]  →  [1번 노드]  →  ...  →  NULL
```

- `org`는 전역 더미 노드로, 실제 데이터를 담지 않고 첫 번째 노드를 가리키는 역할만 합니다.
- 📌 인덱스 기준: `org`는 `-1`번, `org.link`가 가리키는 노드가 `0`번입니다.
- ✅ 더미 헤드 덕분에 **삽입/삭제 시 첫 번째 노드와 나머지 노드를 동일하게 처리**할 수 있습니다.

---

## 🧩 자료구조

```c
typedef int Element;

typedef struct Node {
    Element data;       // 저장 데이터
    struct Node* link;  // 다음 노드 포인터
} Node;

Node org = {0, NULL};  // 전역 더미 헤드 노드
```

---

## 📋 함수 목록

### ⚙️ 초기화 / 상태 확인

| 함수 | 설명 |
|------|------|
| `void init_list()` | 리스트를 초기화합니다 (더미 노드만 남김) |
| `int is_empty()` | 리스트가 비어 있으면 1, 아니면 0 반환 |
| `int is_full()` | 항상 0 반환 (메모리 허용 한에서 무제한) |
| `int size()` | 리스트에 저장된 노드 수 반환 |

---

### ➕ 삽입

```c
void insert(int pos, Element e)
```

`pos`번 위치에 데이터 `e`를 삽입합니다.

- `pos == 0` : 맨 앞에 삽입
- `pos == size()` : 맨 뒤에 삽입
- 💡 내부적으로 `get_node(pos - 1)`을 호출해 이전 노드를 구하며, `pos == 0`일 때 더미 노드 `&org`가 반환되므로 분기 없이 동일하게 처리됩니다.

```c
void append(Element e)
```

리스트 **맨 뒤**에 데이터 `e`를 삽입합니다.

---

### ➖ 삭제

```c
Element delete(int pos)
```

`pos`번 노드를 삭제하고 해당 데이터를 반환합니다.

- ⚠️ 빈 리스트이거나 유효하지 않은 위치면 프로그램을 종료합니다.

```c
Element pop()
```

**맨 뒤** 노드를 삭제하고 해당 데이터를 반환합니다.

```c
void destroy_list()
```

리스트의 **모든** 노드를 삭제합니다.

---

### 🔍 조회 / 수정

```c
Element get_entry(int pos)
```

`pos`번 노드의 데이터를 반환합니다.

```c
void replace(int pos, Element e)
```

`pos`번 노드의 데이터를 `e`로 교체합니다.

```c
int find(Element e)
```

데이터 `e`를 가진 첫 번째 노드의 인덱스를 반환합니다. 없으면 `-1`을 반환합니다.

---

### 🔧 내부 헬퍼

```c
Node* get_node(int pos)      // pos번 노드 포인터 반환 (pos==-1이면 &org 반환)
Node* alloc_node(Element e)  // 노드 동적 할당
Element free_node(Node* p)   // 노드 해제 후 데이터 반환
void error(char* str)        // 오류 메시지 출력 후 프로그램 종료
```

---

## 💻 사용 예시

```c
init_list();

insert(0, 10);   // [10]
insert(1, 20);   // [10, 20]
insert(1, 15);   // [10, 15, 20]
append(30);      // [10, 15, 20, 30]

printf("%d\n", get_entry(2));   // 20
printf("%d\n", find(15));       // 1

replace(0, 99);                 // [99, 15, 20, 30]

delete(1);                      // [99, 20, 30]
pop();                          // [99, 20]

printf("size: %d\n", size());   // 2

destroy_list();                 // []
```

---

## ⏱️ 시간 복잡도

| 연산 | 복잡도 | 비고 |
|------|--------|------|
| `insert(pos, e)` | O(n) | pos까지 순차 탐색 |
| `delete(pos)` | O(n) | pos까지 순차 탐색 |
| `append(e)` | O(n) | tail까지 순차 탐색 |
| `pop()` | O(n) | tail까지 순차 탐색 |
| `get_entry(pos)` | O(n) | pos까지 순차 탐색 |
| `find(e)` | O(n) | 전체 순회 |
| `replace(pos, e)` | O(n) | pos까지 순차 탐색 |
| `size()` | O(n) | 전체 순회 |
| `is_empty()` | **O(1)** | 포인터 확인만 |

> 💬 모든 위치 접근이 O(n)인 것은 연결 리스트의 특성상 순차 탐색이 필요하기 때문입니다.

---
