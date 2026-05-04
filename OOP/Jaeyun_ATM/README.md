C++ 객체지향 프로그래밍으로 구현한 ATM 시뮬레이션 프로젝트입니다.
계좌 개설부터 이체, 관리자 통계까지 실제 ATM의 핵심 기능을 구현하였습니다.

📁 프로젝트 구조
📦 ATM Project
├── 📄 Main.cpp          # 프로그램 진입점, ATMachine 실행 루프
├── 📄 ATMachine.h/.cpp  # ATM 핵심 기능 (메뉴, 거래 처리)
├── 📄 Account.h/.cpp    # 계좌 클래스 (개설, 입출금, 이체, 인증)
├── 📄 Statistics.h/.cpp # 통계 유틸리티 (합계, 평균, 최솟값, 최댓값, 정렬)

🏗️ 클래스 구조
ATMachine
├── Account[]         (동적 배열, 최대 계좌 수)
└── Statistics        (static 유틸 클래스)
🔷 Account
멤버타입설명nIDint계좌번호 (100~999 랜덤, 미사용시 -1)nBalanceint잔고strAccountNamestring고객명strPasswordstring비밀번호
메서드반환값설명create(id, money, name, password)void계좌 개설close()void계좌 해지 (초기화)check(id, password)int잔고 조회deposit(id, password, money)int인증 후 입금deposit(id, money)bool이체용 입금 (인증 없음)widraw(id, password, money)int인증 후 출금

🔐 인증 실패 시 AUTHENTIFICATION_FAIL(-1) 반환


🔷 ATMachine
멤버타입설명pAcctArrayAccount*계좌 동적 배열nMachineBalanceintATM 보유 현금nMaxAccountNumint최대 계좌 수nCurrentAccountNumint현재 개설된 계좌 수strManagerPasswordstring관리자 비밀번호
메서드설명createAccount()계좌 개설 (랜덤 계좌번호 부여)checkMoney()잔고 조회closeAccount()계좌 해지 (잔액 0원일 때만 가능)depositMoney()입금widrawMoney()출금transfer()계좌 이체 (실패 시 자동 롤백)managerMode()관리자 통계 화면

🔷 Statistics (정적 유틸 클래스)
메서드설명sum(pArray, size)전체 고객 잔고 합계average(pArray, size)전체 고객 잔고 평균min(pArray, size)최소 잔고max(pArray, size)최대 잔고sort(pArray, size)잔액 내림차순 버블 정렬 (해지 계좌는 뒤로)

⚙️ 초기 설정
Main.cpp에서 ATM 초기값을 설정합니다.
cppATMachine atm(100, 50000, "admin");
//             ↑     ↑       ↑
//         최대계좌  ATM잔고  관리자암호

💻 메뉴 구성
------------------------
-     TUKOREA BANK     -
------------------------
1. 계좌 개설
2. 계좌 조회
3. 계좌 해지
4. 계좌 입금
5. 계좌 출금
6. 계좌 이체
8. 고객 관리  ← 관리자 전용
9. 업무 종료

🔄 주요 동작 흐름
계좌 개설
이름 / 비밀번호 입력
    → 100~999 랜덤 계좌번호 생성 (중복 시 재생성)
    → 빈 슬롯에 계좌 저장
    → 성공 메시지 출력
계좌 이체
출금 계좌 / 비밀번호 / 이체 계좌 / 금액 입력
    → 출금 계좌에서 출금 시도
    → 성공 시 이체 계좌에 입금
    → 이체 계좌 없거나 오류 → 자동 롤백 💡
관리자 모드 (메뉴 8번)
관리자 비밀번호 입력
    → 인증 성공 시 통계 출력
        - ATM 잔고 / 고객 잔고 총액·평균·최솟값·최댓값
        - 잔액 내림차순 고객 계좌 목록
