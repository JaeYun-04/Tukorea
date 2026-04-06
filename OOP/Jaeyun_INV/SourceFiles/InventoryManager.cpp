#include "InventoryManager.h"

void InventoryManager::addProduct() {
    string name;
    int price, stock;
    cout << "상품명: "; cin >> name;
    cout << "가격: "; cin >> price;
    cout << "초기 재고: "; cin >> stock;
    products.push_back(Product(name, price, stock));
    cout << "등록 완료!\n";
}

void InventoryManager::showAll() {
    cout << "\n--- 전체 재고 목록 ---\n";
    for (const auto& p : products) {
        if (p.isActive()) p.printInfo();
    }
}

void InventoryManager::deleteProduct() {
    string name;
    cout << "삭제할 상품명: "; cin >> name;
    for (auto& p : products) {
        if (p.getName() == name && p.isActive()) {
            p.setActive(false); // active 상태 변경 (과제 요구사항)
            cout << "삭제 완료!\n";
            return;
        }
    }
    cout << "찾는 상품이 없습니다.\n";
}

void InventoryManager::searchProduct() {
    string name;
    cout << "검색할 상품명: "; cin >> name;
    for (const auto& p : products) {
        if (p.getName() == name && p.isActive()) {
            p.printInfo();
            return;
        }
    }
    cout << "검색 결과가 없습니다.\n";
}

void InventoryManager::income() {
    string name;
    int amount;
    cout << "입고 상품명: "; cin >> name;
    for (auto& p : products) {
        if (p.getName() == name && p.isActive()) {
            cout << "입고 수량: "; cin >> amount;
            p.addStock(amount);
            return;
        }
    }
}

void InventoryManager::outcome() {
    string name;
    int amount;
    cout << "출고 상품명: "; cin >> name;
    for (auto& p : products) {
        if (p.getName() == name && p.isActive()) {
            cout << "출고 수량: "; cin >> amount;
            if (p.getStock() >= amount) p.subStock(amount);
            else cout << "재고가 부족합니다.\n";
            return;
        }
    }
}