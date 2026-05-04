#include <iostream>
#include <string>
#include <random>
#include "ATMachine.h"
#include "Statistics.h"

using namespace std;

ATMachine::ATMachine(int size, int balance, string password) {
    nMaxAccountNum = size;
    nMachineBalance = balance;
    nCurrentAccountNum = 0;
    strManagerPassword = password;
    pAcctArray = new Account[size];
}

ATMachine::~ATMachine() {
    delete[] pAcctArray;
}

void ATMachine::displayMenu() {
    cout << "------------------------" << endl;
    cout << "-     TUKOREA BANK     -" << endl;
    cout << "------------------------" << endl;
    cout << "1. 계좌 개설" << endl;
    cout << "2. 계좌 조회" << endl;
    cout << "3. 계좌 해지" << endl;
    cout << "4. 계좌 입금" << endl;
    cout << "5. 계좌 출금" << endl;
    cout << "6. 계좌 이체" << endl;
    cout << "8. 고객 관리" << endl;
    cout << "9. 업무 종료" << endl;
}

void ATMachine::createAccount() {
    string name, password;

    cout << "-------- 개설 --------" << endl;
    cout << "이름 입력: ";
    cin >> name;
    cout << "암호 입력: ";
    cin >> password;

    // 100 ~ 999 사이 랜덤 계좌번호 생성 (중복 확인)
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(100, 999);

    int newID;
    bool isDuplicate;
    do {
        isDuplicate = false;
        newID = dist(gen);
        for (int i = 0; i < nMaxAccountNum; i++) {
            if (pAcctArray[i].getAcctID() == newID) {
                isDuplicate = true;
                break;
            }
        }
    } while (isDuplicate);

    // 빈 슬롯 찾아서 계좌 생성
    for (int i = 0; i < nMaxAccountNum; i++) {
        if (pAcctArray[i].getAcctID() == -1) {
            pAcctArray[i].create(newID, 0, name, password);
            nCurrentAccountNum++;
            cout << name << "님 " << newID << "번 계좌번호가 정상적으로 개설되었습니다. 감사합니다" << endl;
            return;
        }
    }
    cout << "계좌 개설에 실패하였습니다. (최대 계좌 수 초과)" << endl;
}

void ATMachine::checkMoney() {
    int id;
    string password;

    cout << "-------- 조회 --------" << endl;
    cout << "계좌번호 입력: ";
    cin >> id;
    cout << "비밀번호 입력: ";
    cin >> password;

    for (int i = 0; i < nMaxAccountNum; i++) {
        if (pAcctArray[i].getAcctID() == id) {
            int result = pAcctArray[i].check(id, password);
            if (result == AUTHENTIFICATION_FAIL)
                cout << "인증에 실패하였습니다." << endl;
            else
                cout << "현재 잔액 : " << result << endl;
            return;
        }
    }
    cout << "존재하지 않는 계좌번호입니다." << endl;
}

void ATMachine::closeAccount() {
    int id;
    string password;

    cout << "-------- 해지 --------" << endl;
    cout << "계좌번호 입력: ";
    cin >> id;
    cout << "비밀번호 입력: ";
    cin >> password;

    for (int i = 0; i < nMaxAccountNum; i++) {
        if (pAcctArray[i].getAcctID() == id) {
            int result = pAcctArray[i].check(id, password);
            if (result == AUTHENTIFICATION_FAIL) {
                cout << "인증에 실패하였습니다." << endl;
                return;
            }
            if (result > 0) {
                cout << "잔액이 존재하여 해지할 수 없습니다. 잔액: " << result << "원" << endl;
                return;
            }
            pAcctArray[i].close();
            nCurrentAccountNum--;
            cout << id << " 계좌가 해지되었습니다. 감사합니다." << endl;
            return;
        }
    }
    cout << "존재하지 않는 계좌번호입니다." << endl;
}

void ATMachine::depositMoney() {
    int id, money;
    string password;

    cout << "-------- 입금 --------" << endl;
    cout << "계좌번호 입력: ";
    cin >> id;
    cout << "비밀번호 입력: ";
    cin >> password;
    cout << "입금액   입력: ";
    cin >> money;

    for (int i = 0; i < nMaxAccountNum; i++) {
        if (pAcctArray[i].getAcctID() == id) {
            int result = pAcctArray[i].deposit(id, password, money);
            if (result == AUTHENTIFICATION_FAIL)
                cout << "인증에 실패하였습니다." << endl;
            else {
                nMachineBalance += money;
                cout << "현재 잔액 : " << result << endl;
                cout << "입금 완료" << endl;
            }
            return;
        }
    }
    cout << "존재하지 않는 계좌번호입니다." << endl;
}

void ATMachine::widrawMoney() {
    int id, money;
    string password;

    cout << "-------- 출금 --------" << endl;
    cout << "계좌번호 입력: ";
    cin >> id;
    cout << "비밀번호 입력: ";
    cin >> password;
    cout << "출금액   입력: ";
    cin >> money;

    if (nMachineBalance < money) {
        cout << "ATM 잔액이 부족합니다." << endl;
        return;
    }

    for (int i = 0; i < nMaxAccountNum; i++) {
        if (pAcctArray[i].getAcctID() == id) {
            int result = pAcctArray[i].widraw(id, password, money);
            if (result == AUTHENTIFICATION_FAIL)
                cout << "인증에 실패하였습니다." << endl;
            else {
                nMachineBalance -= money;
                cout << "현재 잔액 : " << result << endl;
                cout << "출금 완료" << endl;
            }
            return;
        }
    }
    cout << "존재하지 않는 계좌번호입니다." << endl;
}

void ATMachine::transfer() {
    int fromID, toID, money;
    string password;

    cout << "-------- 이체 --------" << endl;
    cout << "계좌번호 입력: ";
    cin >> fromID;
    cout << "비밀번호 입력: ";
    cin >> password;
    cout << "이체계좌 입력: ";
    cin >> toID;
    cout << "이체금액 입력: ";
    cin >> money;

    // 출금 계좌 찾기
    int fromIdx = -1;
    for (int i = 0; i < nMaxAccountNum; i++) {
        if (pAcctArray[i].getAcctID() == fromID) {
            fromIdx = i;
            break;
        }
    }
    if (fromIdx == -1) {
        cout << "출금 계좌가 존재하지 않습니다." << endl;
        return;
    }

    // 출금 처리
    int result = pAcctArray[fromIdx].widraw(fromID, password, money);
    if (result == AUTHENTIFICATION_FAIL) {
        cout << "인증에 실패하였습니다." << endl;
        return;
    }

    // 입금 계좌 찾기
    for (int i = 0; i < nMaxAccountNum; i++) {
        if (pAcctArray[i].getAcctID() == toID) {
            bool ok = pAcctArray[i].deposit(toID, money);
            if (!ok) {
                // 롤백
                pAcctArray[fromIdx].deposit(fromID, password, money);
                cout << "이체 계좌가 올바르지 않습니다." << endl;
                return;
            }
            cout << "현재 잔액 : " << result << endl;
            cout << "이체 완료" << endl;
            return;
        }
    }

    // 이체 계좌 없으면 롤백
    pAcctArray[fromIdx].deposit(fromID, password, money);
    cout << "이체 계좌가 존재하지 않습니다." << endl;
}

bool ATMachine::isManager(string password) {
    return (password == strManagerPassword);
}

void ATMachine::displayReport() {
    // 정렬 후 출력
    Statistics::sort(pAcctArray, nMaxAccountNum);

    cout << endl;
    cout << "ATM 현재 잔고:    " << nMachineBalance << "원" << endl;
    cout << "고객 잔고 총액:   " << Statistics::sum(pAcctArray, nMaxAccountNum)
         << "원(총 " << nCurrentAccountNum << "명)" << endl;
    cout << "고객 잔고 평균:   " << Statistics::average(pAcctArray, nMaxAccountNum) << "원" << endl;
    cout << "고객 잔고 최소:   " << Statistics::min(pAcctArray, nMaxAccountNum) << "원" << endl;
    cout << "고객 잔고 최고:   " << Statistics::max(pAcctArray, nMaxAccountNum) << "원" << endl;
    cout << "- 고객 계좌 목록 -" << endl;

    int rank = 1;
    for (int i = 0; i < nMaxAccountNum; i++) {
        if (pAcctArray[i].getAcctID() != -1) {
            cout << rank++ << ". " << pAcctArray[i].getAccountName()
                 << "  " << pAcctArray[i].getAcctID()
                 << "  " << pAcctArray[i].getBalance() << "원" << endl;
        }
    }
}

void ATMachine::managerMode() {
    string password;

    cout << "-------- 관리 --------" << endl;
    cout << "관리자 비밀번호 입력: ";
    cin >> password;

    if (!isManager(password)) {
        cout << "관리자 암호가 틀렸습니다." << endl;
        return;
    }

    cout << "관리자입니다." << endl;
    displayReport();
}