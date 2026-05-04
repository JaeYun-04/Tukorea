Element data[MAX_SIZE]; // 데이터를 저장할 스택 공간
int top; // 스택 상단 인덱스

void error(char str[]) 
{
    printf("%s\n", str);
    exit(1);
}

// 스택의 주요 연산들
void init_stack()
{
    top = -1; // 초기상태이거나 비어있을 때는 -1, 데이터가 들어올 때마다 1씩 증가
}

int is_empty()
{
    if (top == -1) return 1; // top이 1이면 데이터가 하나도 없다는 뜻이므로 0을 반환 
    else return 0;
} 

int is_full() 
{
    return (top == (MAX_SIZE - 1)); // 더 이상 저장할 공간이 없다는 뜻
    
}

// 
void push(Element e)
{
    if(is_full())
    error("Overflow!"); // 데이터가 포화상태이면 오버플로 에러 출력!
    else
    data[++top] = e;    
}

Element pop()
{
    if(is_empty()) // 데이터가 비어 있으면 언더플로 에러 출력!
    error("Underflow Error!");
    else 
    return data[top--]; // 현재 top 위치에 있는 값을 먼저 반환하고, 그 후에 top을 1 감소시킨다.
}

Element peek() 
{
    if (is_empty())  // 맨 위에 뭐가 있는지 확인하는 용도
        error("Underflow Error!");
    return data[top];
}

