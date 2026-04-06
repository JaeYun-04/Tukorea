#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

class Product {
private:
    string name; // 상품 이름
    int price; // 상품 가격
    int stock;  // 상품 재고
    bool active; // 삭제 상태 관리용

public:
    Product(string n, int p, int s);
    
    string getName() const { return name; }
    int getPrice() const { return price; }
    int getStock() const { return stock; }
    bool isActive() const { return active; }

    void setActive(bool status) { active = status; }
    void addStock(int amount) { stock += amount; }
    void subStock(int amount) { stock -= amount; }
    
    void printInfo() const;
};

#endif