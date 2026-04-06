#include "Product.h"
#include <iomanip>

Product::Product(string n, int p, int s) : name(n), price(p), stock(s), active(true) {}

void Product::printInfo() const { 
    cout << left << setw(15) << name << " | 가격: " << setw(7) << price 
         << " | 재고: " << setw(5) << stock << " | 상태: " << (active ? "판매중" : "품절(삭제)") << endl;
}