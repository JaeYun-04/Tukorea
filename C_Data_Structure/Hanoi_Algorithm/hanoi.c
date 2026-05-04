#include <stdio.h>

int move_count = 0; // 탑 이동 횟수

void hanoi(int n, char start_pos, char temp, char arrive_pos) {
    if (n == 1) {
        move_count++;
        printf("원판 1을 %c에서 %c로 이동 (이동 횟수: %d)\n", start_pos, arrive_pos, move_count);
    } else {
        // 1. n-1개의 탑을 '시작'에서 '보조' 기둥으로 이동
        hanoi(n - 1, start_pos, arrive_pos, temp);
        
        // 2. 가장 큰 탑을 '시작'에서 '목적지'기둥으로 이동
        move_count++;
        printf("원판 %d를 %c에서 %c로 이동 (이동 횟수: %d)\n", n, start_pos, arrive_pos, move_count);
        
        // 3. '보조' 기둥에 있는 n-1개의 탑을 '목적지' 기둥으로 이동
        hanoi(n - 1, temp, start_pos, arrive_pos); 
    }
}

int main() {
    int n = 3;
    printf("원판 %d개의 하노이 탑 이동 순서:\n", n);
    hanoi(n, 'A', 'B', 'C');
    printf("총 이동 횟수: %d\n", move_count);
    return 0;
}