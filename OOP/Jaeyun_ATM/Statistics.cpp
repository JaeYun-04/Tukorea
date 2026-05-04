#include "Statistics.h"

int Statistics::sum(Account* pArray, int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        if (pArray[i].getAcctID() != -1)
            total += pArray[i].getBalance();
    }
    return total;
}

int Statistics::average(Account* pArray, int size) {
    int count = 0;
    int total = 0;
    for (int i = 0; i < size; i++) {
        if (pArray[i].getAcctID() != -1) {
            total += pArray[i].getBalance();
            count++;
        }
    }
    if (count == 0) return 0;
    return total / count;
}

int Statistics::min(Account* pArray, int size) {
    int minVal = -1;
    for (int i = 0; i < size; i++) {
        if (pArray[i].getAcctID() != -1) {
            if (minVal == -1 || pArray[i].getBalance() < minVal)
                minVal = pArray[i].getBalance();
        }
    }
    return (minVal == -1) ? 0 : minVal;
}

int Statistics::max(Account* pArray, int size) {
    int maxVal = 0;
    for (int i = 0; i < size; i++) {
        if (pArray[i].getAcctID() != -1) {
            if (pArray[i].getBalance() > maxVal)
                maxVal = pArray[i].getBalance();
        }
    }
    return maxVal;
}

// 버블 정렬 (잔액 내림차순)
void Statistics::sort(Account* pArray, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            // 해지된 계좌는 뒤로 보냄
            bool jInvalid = (pArray[j].getAcctID() == -1);
            bool j1Invalid = (pArray[j + 1].getAcctID() == -1);

            if (jInvalid && !j1Invalid) {
                Account temp = pArray[j];
                pArray[j] = pArray[j + 1];
                pArray[j + 1] = temp;
            } else if (!jInvalid && !j1Invalid) {
                if (pArray[j].getBalance() < pArray[j + 1].getBalance()) {
                    Account temp = pArray[j];
                    pArray[j] = pArray[j + 1];
                    pArray[j + 1] = temp;
                }
            }
        }
    }
}