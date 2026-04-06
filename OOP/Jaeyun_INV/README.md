TUK 객체지향언어 과제 문제

📦 Inventory Management System (C++)
객체지향 프로그래밍(OOP)을 활용한 콘솔 기반 재고 관리 프로그램입니다. 상품의 등록,조회,삭제(상태 관리) 및 입출고 기능을 제공합니다.

🛠 Tech Stack
Language: C++ 
Tools: Visual Studio Code
Key Concept: Object-Oriented Programming (Encapsulation, Class Separation)

🏗 System Architecture
본 프로그램은 역할에 따라 3개의 모듈로 분리되어 설계되었습니다.
Product: 상품의 속성(이름, 가격, 재고, 활성 상태)과 데이터를 다루는 가상 객체.

InventoryManager: 상품 객체들을 std::vector로 관리하며 비즈니스 로직(등록, 검색, 수정)을 수행.

Main: 사용자 인터페이스(UI) 및 메뉴 제어 루프 담당.

📌 Key Features
1. 상품 등록 및 전체 목록 조회
   
새로운 상품 객체를 생성하여 리스트에 추가합니다.
전체 목록 출력 시 현재 '판매 중(Active)'인 상품만 필터링하여 보여줍니다.

2. 논리적 삭제 (Soft Delete)
Active 상태 변경: 실제 데이터를 메모리에서 즉시 지우지 않고, active 플래그를 false로 변경하여 관리합니다. 이는 데이터 복구 및 이력 관리에 유리한 실무적인 방식입니다.

3. 입고 및 출고 관리
특정 상품을 검색하여 재고 수량을 증감시킵니다.
예외 처리: 출고 시 현재 재고보다 많은 수량을 입력하면 "재고 부족" 메시지를 출력하여 데이터 무결성을 유지합니다.

📂 Project Structure
Plaintext
Jaeyun_INV/

├── Product.h              # Product 클래스 선언

├── Product.cpp            # Product 클래스 구현

├── InventoryManager.h     # 관리 로직 선언

├── InventoryManager.cpp   # 관리 로직 구현

└── Main.cpp               # 메인 진입점 및 메뉴 UI
