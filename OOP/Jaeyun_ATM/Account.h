#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using std::string;

#define AUTHENTIFICATION_FAIL    -1   // 계정 인증 실패
#define AUTHENTIFICATION_SUCCESS  1   // 계정 인증 성공

class Account {
private:
    int nID;                  // 계좌 번호 (초기 값 = -1), 계좌 해지시 초기값으로 변경
    int nBalance;             // 잔고 (초기 값 = 0)
    string strAccountName;    // 고객 명
    string strPassword;       // 계좌 비밀번호

private:
    inline bool authenticate(int id, string passwd) {
        return (nID == id && strPassword == passwd);
    }

public:
    Account();

    void create(int id, int money, string name, string password); // 계좌 개설
    void close();                                                  // 계좌 해지 (잔액 존재시 불가)

    int check(int id, string password);       // return: nBalance(잔고) or AUTHENTIFICATION_FAIL
    int deposit(int id, string password, int money);  // 입금, return: nBalance or AUTHENTIFICATION_FAIL
    int widraw(int id, string password, int money);   // 출금, return: nBalance or AUTHENTIFICATION_FAIL
    bool deposit(int id, int money);                  // 이체용 입금 (송금 계좌와 이체 금액), return: bool

    int getAcctID() { return nID; }
    int getBalance() { return nBalance; }
    string getAccountName() { return strAccountName; }
};

#endif