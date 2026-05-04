#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <vector>
#include "Product.h"

class InventoryManager {
private:
    vector<Product> products;

public:
    
    void addProduct(); // 상품 등록 기능입니다
    void showAll();
    void deleteProduct(); // 상품 삭제 기능입니다
    
    // 추가 기능
    void searchProduct(); // 검색
    void income(); // 입고
    void outcome(); // 출고
};

#endif