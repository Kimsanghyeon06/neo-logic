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
                cout << "■ ";
            else
                cout << "□ ";
        }
        cout << endl;
    }
}

//힌트 출력
void printhint_row(int row[5]) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (row[i] == 1) {
            count++;
        }
        else {
            if (count > 0) {
                cout << count << " ";
            }
            count = 0;
        }
    }
    if (count > 0) {
        cout << count << " ";
    }
}
void printhint_col(int puzzle[5][5]) {
    cout << "가로: \n";
    for (int i = 0; i < 5; i++) {
        printhint_row(puzzle[i]);
        cout << "\n";
    }
    cout << "세로: \n";
    for (int j = 0; j < 5; j++) {
        int temp_col[5];
        for (int i = 0; i < 5; i++) {
            temp_col[i] = puzzle[i][j];
        }
        printhint_row(temp_col);
        cout << "\n";
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
    printhint_col(puzzles[puzzle_index]); //힌트 출력

    string input;
    while (life > 0) {
        printPuzzle(user_choice);
        cout << "목숨: " << life << " | 칸 선택 예: A1" << endl;
        cout << "좌표 입력: ";
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

        if (user_choice[row][col] == 1) {
            cout << "이미 선택한 칸입니다.\n" << endl;
            continue;
        }

        if (checkAnswer(row, col)) {
            cout << "---------------\n";
            cout << "  정답입니다!\n";
            cout << "---------------\n";
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

        //최종결과 출력
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (puzzles[puzzle_index][i][j] != user_choice[i][j]) {
                    Finished = false;
                    break;
                }
            }
            if (!Finished) break;
        }

        if (Finished) {
            cout << "\n최종 결과:\n";
            printPuzzle(user_choice);
            cout << "\n축하합니다! 퍼즐을 완성했습니다!\n";
            break;
        }
    }


    if (life <= 0)
        cout << "GAME OVER\n" << "정답 : \n", printPuzzle(puzzles[puzzle_index]);

    return 0;
}