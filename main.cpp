#include <iostream>
#include <cctype>
#include <string>
using namespace std;

int life = 3;
int puzzles[10][5][5] = {
    {{0,1,0,1,0},{1,1,1,1,1},{1,1,1,1,1},{0,1,1,1,0},{0,0,1,0,0}}, // 하트
    {{0,0,1,0,0},{0,0,1,0,0},{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0}}, // 십자가
    {{0,1,0,1,0},{0,1,0,1,0},{0,0,0,0,0},{1,0,0,0,1},{0,1,1,1,0}}, // 웃는얼굴
    {{0,0,1,0,0},{0,1,0,1,0},{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0}}, // 다이아몬드
    {{1,1,1,1,1},{1,0,0,0,0},{1,1,1,1,0},{0,0,0,0,1},{1,1,1,1,0}}, // 숫자 5
    {{1,1,1,1,1},{0,0,1,0,0},{1,1,1,1,1},{0,1,0,1,0},{1,1,1,1,1}}, // 벽돌탑
    {{0,0,1,0,0},{0,1,1,1,0},{1,0,1,0,1},{0,0,1,0,0},{0,0,1,0,0}}, // 하강 화살표
    {{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}}, // T자
    {{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1}}, // 테두리
    {{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0},{0,1,0,1,0},{1,0,0,0,1}}  // X자
};

int user_choice[5][5] = { 0 };  // 사용자가 정답 입력하는 보드
int puzzle_index = 0; // 선택한 퍼즐 번호

void printPuzzle(int arr[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (arr[i][j] == 1)
                cout << "■";
            else
                cout << "□";
        }
        cout << endl;
    }
}

int alphatonum(char ch) {
    return tolower(ch) - 'a';  // a->0, b->1, ...
}

bool checkAnswer(int row, int col) {
    if (puzzles[puzzle_index][row][col] == 1) {
        user_choice[row][col] = 1;
        return true;
    }
    else {
        life--;
        return false;
    }
}

int main() {
    cout << "0~9 사이의 퍼즐 번호를 선택하세요: ";
    cin >> puzzle_index;

    string input;
    while (life > 0) {
        printPuzzle(user_choice);
        cout << "목숨: " << life << " | 칸 선택 예: A1" << endl;
        cin >> input;

        if (input.length() < 2) {
            cout << "입력이 잘못되었습니다." << endl;
            continue;
        }

        int row = alphatonum(input[0]); // A~E → 0~4
        int col = input[1] - '1'; // 1~5 → 0~4

        if (row < 0 || row >= 5 || col < 0 || col >= 5) {
            cout << "잘못된 위치입니다." << endl;
            continue;
        }

        if (checkAnswer(row, col)) {
            cout << "정답입니다!\n";
        }
        else {
            cout << "틀렸습니다. 목숨 -1\n";
        }

        // 승리 조건 확인
        bool Finished = true;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (puzzles[puzzle_index][i][j] == 1 && user_choice[i][j] == 0)
                    Finished = false;

        if (Finished) {
            cout << "퍼즐을 완성했습니다 \n";
            break;
        }
    }

    if (life <= 0)
        cout << "GAME OVER\n" << "정답 : \n", printPuzzle(puzzles[puzzle_index]);

    return 0;
}
