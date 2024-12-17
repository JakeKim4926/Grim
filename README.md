# 💻 구현 환경
- Visual Studio 2022 Community
- C++/MFC (대화 상자 기반)
<br>

# 🔍 구현 사항

0. 폴더의 Task1은 유튜브 과제, Task2는 프로그래머스 과제 파일 경로로 설정하였습니다.
1. 요구 사항 1번 구현을 위하여 다이얼로그 중단에 이미지를 표시하였습니다.
2. 요구 사항 2번 구현을 위하여 좌표값들을 상단에 입력 받을 수 있도록 배치하였습니다.
3. 요구 사항 3번 구현을 위하여 예외 처리 조건을 설정하여 이미지를 출력하였습니다.
<br>(**pch.h**의 **MOVE_VALUE** 값을 수정하여 원 픽셀값들의 움직임 폭을 조절할 수 있습니다.)
4. 요구 사항 4번 구현을 위하여 쓰레드 생성 후 (x1,y1), (x2,y2) 이동 조건과 예외 처리 조건을 설정 후 저장하였습니다.
5. 요구 사항 5번 구현을 위하여 이미지 불러오기 기능 설정 후 4번에서 생성한 원을 검출 할 수 있도록 조건을 설정하였습니다.

<br>

# 🧮 커밋 컨벤션
- **feat**: 새로운 기능 추가
    - 예: `feat: add user login functionality`
- **fix**: 버그 수정
    - 예: `fix: resolve issue with user login`
- **docs**: 문서 수정
    - 예: `docs: update API documentation`
- **refactor**: 코드 리팩토링; 기능 변경 없음
    - 예: `refactor: simplify user login logic`
- **init**: 최초 환경 설정
    - 예: `init: init dlg with MFC`
- **revert**: 이전 커밋을 되돌릴 때 사용
    - 예: `revert: revert commit 1234567`

<br>

# 📃 파일 구조
📦Grim
<br>┣ 📂Task1
<br>┃ ┗ 📂GrimTask
<br>┃ ┃ ┗ 📜GrimTask.sln
<br>┃ ┃ ┣ 📂GrimTask
<br>┃ ┃ ┃ ┣ 📂res
<br>┃ ┃ ┃ ┃ ┣ 📜GrimTask.ico
<br>┃ ┃ ┃ ┃ ┗ 📜GrimTask.rc2
<br>┃ ┃ ┃ ┣ 📜framework.h
<br>┃ ┃ ┃ ┣ 📜GrimCV.cpp
<br>┃ ┃ ┃ ┣ 📜GrimCV.h
<br>┃ ┃ ┃ ┣ 📜GrimTask.cpp
<br>┃ ┃ ┃ ┣ 📜GrimTask.h
<br>┃ ┃ ┃ ┣ 📜GrimTask.rc
<br>┃ ┃ ┃ ┣ 📜GrimTask.vcxproj
<br>┃ ┃ ┃ ┣ 📜GrimTask.vcxproj.filters
<br>┃ ┃ ┃ ┣ 📜GrimTask.vcxproj.user
<br>┃ ┃ ┃ ┣ 📜GrimTaskDlg.cpp
<br>┃ ┃ ┃ ┣ 📜GrimTaskDlg.h
<br>┃ ┃ ┃ ┣ 📜pch.cpp
<br>┃ ┃ ┃ ┣ 📜pch.h
<br>┃ ┃ ┃ ┣ 📜resource.h
<br>┣ 📂Task2
<br>┃ ┣ 📜2-1_양꼬치.jpg
<br>┃ ┣ 📜2-1_양꼬치.txt
<br>┃ ┣ 📜2-2_접두사인지 확인하기.jpg
<br>┃ ┣ 📜2-2_접두사인지 확인하기.txt
<br>┃ ┣ 📜2-3_햄버거 만들기.jpg
<br>┃ ┣ 📜2-3_햄버거 만들기.txt
<br>┃ ┣ 📜2-4_더 크게 합치기.jpg
<br>┃ ┣ 📜2-4_더 크게 합치기.txt
<br>┃ ┣ 📜2-5_이차원 배열 대각선 순회하기.jpg
<br>┃ ┣ 📜2-5_이차원 배열 대각선 순회하기.txt
<br>┃ ┣ 📜2-6_두 원 사이의 정수 쌍.jpg
<br>┃ ┗ 📜2-6_두 원 사이의 정수 쌍.txt
<br>┣ 📜.gitignore
<br>┗ 📜README.md
