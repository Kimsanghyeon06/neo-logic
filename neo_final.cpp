#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
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

string puzzle_name[10] = {
    "하트","십자가","웃는얼굴","다이아몬드","숫자 5","벽돌탑","하강 화살표","T자","테두리","X자"
};

int user_choice[5][5] = { 0 };  // 사용자가 정답 입력하는 보드
int puzzle_index = 0; // 선택한 퍼즐 번호


class Hint {
public:

    void Hint_Puzzle(int puzzle[5][5], int user[5][5]);
};


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

void Hint::Hint_Puzzle(int puzzle[5][5], int user[5][5]) {
    int col_H[5][3] = { 0 };
    int col_H_Count[5] = { 0 };

    // 열 힌트 계산
    for (int col = 0; col < 5; col++) {
        int count = 0, index = 0;
        for (int i = 0; i < 5; i++) {
            if (puzzle[i][col] == 1) count++;
            else if (count > 0) {
                col_H[col][index++] = count;
                count = 0;
            }
        }
        if (count > 0) col_H[col][index++] = count;
        if (index == 0) col_H[col][index++] = 0;
        col_H_Count[col] = index;
    }

    // 열 힌트 출력 (최대 2줄만 출력)
    for (int line = 0; line < 3; line++) {
        cout << "   ";
        for (int col = 0; col < 5; col++) {
            int hintIndex = col_H_Count[col] - 3 + line;
            if (hintIndex >= 0)
                cout << " " << col_H[col][hintIndex];
            else
                cout << "  ";
        }
        cout << endl;
    }

    // 행 힌트 + 퍼즐 출력
    for (int i = 0; i < 5; i++) {
        int row_H[3] = { 0 };
        int count = 0, index = 0;
        for (int j = 0; j < 5; j++) {
            if (puzzle[i][j] == 1) count++;
            else if (count > 0) {
                row_H[index++] = count;
                count = 0;
            }
        }
        if (count > 0) row_H[index++] = count;
        if (index == 0) row_H[index++] = 0;

        // 행 힌트 출력 (최대 2칸 오른쪽 정렬)
        if (index == 1)
            cout << "  " << row_H[0];
        else
            cout << row_H[0] << " " << row_H[1];

        cout << " ";

        // 퍼즐 출력
        for (int j = 0; j < 5; j++) {
            if (user[i][j] == 1)
                cout << "■ ";
            else
                cout << "□ ";
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
    Hint hint;
    cout << "0~9 사이의 퍼즐 번호를 선택하세요: ";
    cin >> puzzle_index;
    cout << "Hint:" << puzzle_name[puzzle_index] << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string input_num;
    while (life > 0) {
        hint.Hint_Puzzle(puzzles[puzzle_index], user_choice);
        cout << "목숨: " << life << " (칸 선택 예: A1)" << endl;
        cout << "좌표 선택: ";

        getline(cin, input_num);
        stringstream stream(input_num);
        bool cor = false;
        bool wro = false;
        int wro_count = 0;
        vector<string> incor_temp;

        while (stream >> input_num) {
            if (input_num.length() != 2) {
                cout << "입력이 잘못되었습니다." << endl;
                continue;
            }

            int row = alphatonum(input_num[0]); // A~E → 0~4
            int col = input_num[1] - '1'; // 1~5 → 0~4

            if (row < 0 || row >= 5 || col < 0 || col >= 5) {
                cout << "잘못된 위치입니다." << endl;
                continue;
            }

            if (user_choice[row][col] == 1) {
                cout << "이미 선택한 칸입니다." << endl;
                continue;
            }

            bool correct = checkAnswer(row, col);
            if (correct) {
                cor = true;
            }
            else {
                wro = true;
                incor_temp.push_back(input_num);
                wro_count++;
            }
        }

        if (cor || wro) {
            cout << "\n---------------\n";
            if (cor) {
                cout << "  정답입니다!\n";

            }
            if (wro) {
                cout << wro_count << "개 틀렸으므로 목숨이 " << wro_count << "개 차감되었습니다!\n";
            }
            cout << "---------------\n";
        }
        // 승리 조건 확인
        bool Finished = true;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (puzzles[puzzle_index][i][j] == 1 && user_choice[i][j] == 0)
                    Finished = false;

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