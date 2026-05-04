#include "InventoryManager.h"

int main() {
    InventoryManager manager;
    int choice;

    while (true) {  
        cout << "\n1.등록 2.목록 3.삭제 4.검색 5.입고 6.출고 0.종료 : ";
        cin >> choice;

        if (choice == 0) break; // break로 빠져나가기
        switch (choice) { // case문 활용하기
            case 1: manager.addProduct(); break;
            case 2: manager.showAll(); break;
            case 3: manager.deleteProduct(); break;
            case 4: manager.searchProduct(); break;
            case 5: manager.income(); break;
            case 6: manager.outcome(); break;
            default: cout << "잘못된 입력입니다.\n";
        }
    }
    return 0;
}