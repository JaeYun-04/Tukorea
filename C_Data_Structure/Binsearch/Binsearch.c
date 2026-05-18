#include <stdio.h>
#include <stdlib.h>

// ================================================================
// 노드 구조체
// ================================================================
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// ================================================================
// 노드 생성
// ================================================================
Node* alloc_node(int data)

{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data  = data;
    p->left  = NULL;
    p->right = NULL;
    return p;
}

// ================================================================
// 탐색 (Search)
// 찾으면 해당 노드 포인터 반환, 없으면 NULL 반환
// ================================================================
Node* search(Node* root, int target)
{
    if (root == NULL) {
        return NULL;                    // 탐색 실패
    }
    if (target == root->data) {
        return root;                    // 탐색 성공
    } else if (target < root->data) {
        return search(root->left, target);  // 왼쪽 서브트리 탐색
    } else {
        return search(root->right, target); // 오른쪽 서브트리 탐색
    }
}

// ================================================================
// 삽입 (Insert)
// 중복 데이터는 삽입하지 않음
// ================================================================
Node* insert(Node* root, int data)
{
    if (root == NULL) {
        return alloc_node(data);        // 빈 자리에 새 노드 생성
    }
    if (data < root->data) {
        root->left  = insert(root->left,  data); // 왼쪽 서브트리에 삽입
    } else if (data > root->data) {
        root->right = insert(root->right, data); // 오른쪽 서브트리에 삽입
    } else {
        printf("  [삽입 실패] %d는 이미 존재하는 값입니다.\n", data);
    }
    return root;
}

// ================================================================
// 최솟값 노드 찾기 (삭제 시 중위 후계자 탐색에 사용)
// ================================================================
Node* find_min(Node* root)
{
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// ================================================================
// 삭제 (Delete)
// case 1: 자식 없음  → 그냥 삭제
// case 2: 자식 1개   → 자식으로 대체
// case 3: 자식 2개   → 오른쪽 서브트리의 최솟값(중위 후계자)으로 대체
// ================================================================
Node* delete(Node* root, int target)
{
    if (root == NULL) {
        printf("  [삭제 실패] %d를 찾을 수 없습니다.\n", target);
        return NULL;
    }

    if (target < root->data) {
        root->left  = delete(root->left,  target);
    } else if (target > root->data) {
        root->right = delete(root->right, target);
    } else {
        // 삭제 대상 노드 발견
        if (root->left == NULL && root->right == NULL) {
            // case 1: 단말 노드
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // case 2: 오른쪽 자식만 있음
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            // case 2: 왼쪽 자식만 있음
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            // case 3: 자식이 둘 다 있음 → 중위 후계자로 대체
            Node* successor = find_min(root->right);
            root->data  = successor->data;
            root->right = delete(root->right, successor->data);
        }
    }
    return root;
}

// ================================================================
// 트리 전체 메모리 해제
// ================================================================
void destroy_tree(Node* root)
{
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// ================================================================
// 출력: 중위 순회 (In-order) → 오름차순 출력
// ================================================================
void inorder(Node* root)
{
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// ================================================================
// 트리 구조 시각화 (회전된 형태로 출력)
// ================================================================
void print_tree(Node* root, int depth)
{
    if (root == NULL) return;
    print_tree(root->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("[%d]\n", root->data);
    print_tree(root->left, depth + 1);
}

// ================================================================
// 탐색 헬퍼: 결과 출력 포함
// ================================================================
void search_and_print(Node* root, int target)
{
    Node* result = search(root, target);
    if (result != NULL) {
        printf("  탐색 성공: %d 발견!\n", result->data);
    } else {
        printf("  탐색 실패: %d 없음\n", target);
    }
}

// ================================================================
// 메인 함수
// ================================================================
int main()
{
    Node* root = NULL;

    // ── 1. 노드 10개 삽입 ──────────────────────────────────────
    printf("================================================================\n");
    printf("  [삽입] 10개의 노드 삽입\n");
    printf("================================================================\n");

    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 35, 65};
    for (int i = 0; i < 10; i++) {
        printf("  %d 삽입\n", values[i]);
        root = insert(root, values[i]);
    }

    printf("\n중위 순회 (오름차순): ");
    inorder(root);
    printf("\n\n트리 구조 (오른쪽이 위):\n");
    print_tree(root, 0);

    // ── 2. 탐색 ────────────────────────────────────────────────
    printf("\n================================================================\n");
    printf("  [탐색]\n");
    printf("================================================================\n");
    search_and_print(root, 40);  // 존재하는 값
    search_and_print(root, 65);  // 존재하는 값
    search_and_print(root, 99);  // 존재하지 않는 값

    // ── 3. 삭제 ────────────────────────────────────────────────
    printf("\n================================================================\n");
    printf("  [삭제]\n");
    printf("================================================================\n");

    // case 1: 단말 노드 삭제 (자식 없음)
    printf("\n  case 1 - 단말 노드 삭제: 10\n");
    root = delete(root, 10);
    printf("  중위 순회: "); inorder(root); printf("\n");

    // case 2: 자식 1개인 노드 삭제
    printf("\n  case 2 - 자식 1개 노드 삭제: 20\n");
    root = delete(root, 20);
    printf("  중위 순회: "); inorder(root); printf("\n");

    // case 3: 자식 2개인 노드 삭제
    printf("\n  case 3 - 자식 2개 노드 삭제: 30\n");
    root = delete(root, 30);
    printf("  중위 순회: "); inorder(root); printf("\n");

    // 존재하지 않는 노드 삭제 시도
    printf("\n  존재하지 않는 노드 삭제 시도: 99\n");
    root = delete(root, 99);

    // ── 4. 최종 트리 상태 ──────────────────────────────────────
    printf("\n================================================================\n");
    printf("  [최종 상태]\n");
    printf("================================================================\n");
    printf("중위 순회 (오름차순): ");
    inorder(root);
    printf("\n\n트리 구조 (오른쪽이 위):\n");
    print_tree(root, 0);

    destroy_tree(root);
    return 0;
}