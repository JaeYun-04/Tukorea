<div align="center">

# 🔍 Binary Search Algorithms in C

**이진 탐색 · 보간 탐색** 세 가지 방식의 C언어 구현 및 비교

---

##  개요

정렬된 배열에서 특정 값을 효율적으로 탐색하는 세 가지 알고리즘을 구현하고 비교합니다.

| 구현 함수 | 방식 | 특징 |
|-----------|------|------|
| `binary_search` | 이진 탐색 (재귀) | 재귀 호출로 탐색 범위를 절반씩 줄임 |
| `binary_search_iter` | 이진 탐색 (반복) | while 루프 사용, 스택 오버헤드 없음 |
| `binary_search_interpolation` | 보간 탐색 (재귀) | 값의 분포를 추정해 탐색 위치 계산 |

---

##  알고리즘 설명

### 1. 이진 탐색 — 재귀 (Binary Search, Recursive)

중앙값(`mid`)과 키를 비교해 탐색 범위를 반씩 줄이며 재귀 호출합니다.

```c
int binary_search(int A[], int key, int low, int high) {
    if (low <= high) {
        int mid = (low + high) / 2;
        if (key == A[mid])       return mid;
        else if (key < A[mid])   return binary_search(A, key, low, mid - 1);
        else                     return binary_search(A, key, mid + 1, high);
    }
    return -1;
}
```

### 2. 이진 탐색 — 반복 (Binary Search, Iterative)

재귀 없이 `while` 루프로 동일한 로직을 구현합니다. 스택 메모리를 사용하지 않아 실무에서 선호됩니다.

```c
int binary_search_iter(int A[], int key, int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (key == A[mid])       return mid;
        else if (key < A[mid])   high = mid - 1;
        else                     low  = mid + 1;
    }
    return -1;
}
```

### 3. 보간 탐색 (Interpolation Search)

키 값이 배열의 어느 위치쯤 있을지 **선형 보간**으로 추정해 `mid`를 계산합니다.  
데이터가 균등하게 분포된 경우 이진 탐색보다 빠릅니다.

```c
// mid 추정 공식
int mid = (int)((float)(key - A[low]) / (A[high] - A[low]) * (high - low)) + low;
```

> ⚠️ 데이터 분포가 불균등하면 추정이 빗나가 성능이 오히려 저하될 수 있습니다.

---

##  성능 비교

| 항목 | 이진 탐색 (재귀) | 이진 탐색 (반복) | 보간 탐색 |
|------|:---:|:---:|:---:|
| 평균 시간 복잡도 | O(log n) | O(log n) | **O(log log n)** |
| 최악 시간 복잡도 | O(log n) | O(log n) | O(n) |
| 공간 복잡도 | O(log n) | **O(1)** | O(log n) |
| 균등 분포 성능 | 보통 | 보통 | ✅ 빠름 |
| 불균등 분포 성능 | 보통 | 보통 | ❌ 느릴 수 있음 |
| 스택 사용 | 있음 | **없음** | 있음 |

---

## 🖥️ 실행 예시

### 입력 배열

```c
int list[16] = { 8, 11, 42, 75, 76, 79, 80, 83, 85, 88, 89, 91, 93, 95, 98, 100 };
```

### 탐색 키: `75`

```
이진탐색(순환): ->83->11->42->75   결과: 인덱스 3
이진탐색(보간): ->42->75           결과: 인덱스 3
```

> 이 배열은 앞쪽에 작은 값이 몰려 있어 **보간 탐색에 불리한 분포**입니다.  
> 키를 `25`처럼 균등 분포에 가까운 값으로 바꾸면 보간 탐색이 더 적은 비교로 탐색합니다.
