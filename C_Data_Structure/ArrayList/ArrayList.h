// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch06/ArrayList.h
//--------------------------------------------------------------------
// 코드 6.1 배열 구조의 리스트

// 리스트의 데이터(Element와 MAX_SIZE는 미리 정의되어 있어야 함)
Element data[MAX_SIZE]; // 요소의 배열
int size = 0;           // 요소의 수

void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

// 리스트의 연산들
void init_list() { 
    size = 0; 
}

int is_empty() { 
    return size == 0; 
}

int is_full() { 
    return size == MAX_SIZE; 
}

// 삽입 연산
void insert(int pos, Element e)
{
    if (is_full()) {
        error("Overflow Error!");
    }

    // 현재 size 만큼의 데이터가 list에 존재하는 경우,
    // 0 <= pos <= size 추가 가능(인덱스 pos 유효하다)
    if (pos < 0 || pos > size) {
        error("Invalid Position Error!");
    }

    // pos 위치에 새로운 값 e 추가하기...
    // - 새로운 노드 추가를 위해 공간 마련하기.
    // - 공간에 값 추가하고, size 값 변경하기.
    for(int i = size -1; i >= pos; i--){
        data[i+1] = data[i];
    }
    data[pos] = e;
    size++;
}

// 삭제 연산
Element delete(int pos)
{
    if (is_empty()) {
        error("Underflow Error!");
    }

    // 정상범위 0<= pos <=size-1
    if (pos < 0 || pos >= size) {
        error("Invalid Position Error!");
    }
    
    // pos 위치에 값 제거하고, 제가한 값 반환하기
    // - 값을 제거하기 전에 해당 값 e에 저장하기.
    // - 값 제거하면서 제거된 공간은 당겨서 채우기.
    // - size 값 조정하기.
    Element e = data[pos];
    for(int i = pos; i < size -1; i++){
        data[i] = data[i+1];
    }
    
    size --;
    return e;
}

// 참조 연산
Element get_entry(int pos)
{
    if (is_empty()) {
        error("Underflow Error!");
    }
    if (pos < 0 || pos >= size) {
        error("Invalid Position Error!");
    }
    return data[pos];
}

//--------------------------------------------------------------------
// 코드 6.3 배열 구조의 리스트의 추가 연산

void append(Element e)
{
    // - 마지막 다음 위치에 새로운 값 추가하기.
    insert(size,e);
}

Element pop()
{
    // 맨 마지막 위치의 값 제거하고, 제거된 값 반환하기.
    if(is_empty()){
        error("Underflow Error!");
    }
    return delete(size - 1);
}

void replace(int pos, Element e)
{
    // pos 위치가 유효한 지 먼저 확인.
    if (pos < 0 || pos >= size) {
        error("Invalid Position Error!");
    }

    // pos 위치의 값을 e로 대체하기.
    data[pos] = e;
}

int find(Element e)
{
    // 전체 리스트 공간에서 e값이 있는 지 확인하고 있으면 해당 위치 값을 반환.
    // 없으면 -1 반환하기.

    for (int i = 0; i < size; i++) {
        if (data[i] == e)
            return i;
    }
    return -1;
}
//--------------------------------------------------------------------
