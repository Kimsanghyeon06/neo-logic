#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int life = 3;
int hint_count = 2;
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

// 함수 선언
vector<int> getRowHints(int row);
vector<int> getColHints(int col);

void printNonogramHints() {
    // 열 힌트를 세로로 출력하기 위해 최대 높이 구하기
    int maxColHintHeight = 0;
    vector<vector<int>> allColHints;
    for (int j = 0; j < 5; j++) {
        vector<int> colHints = getColHints(j);
        allColHints.push_back(colHints);
        if (colHints.size() > maxColHintHeight) {
            maxColHintHeight = colHints.size();
        }
    }

    // 열 힌트를 세로로 출력
    for (int height = maxColHintHeight - 1; height >= 0; height--) {
        cout << "    "; // 행 힌트 공간
        for (int j = 0; j < 5; j++) {
            if (height < allColHints[j].size()) {
                cout << allColHints[j][height] << " ";
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    // 구분선
    cout << "   +";
    for (int j = 0; j < 5; j++) {
        cout << "--";
    }
    cout << endl;

    // 행 힌트와 격자 출력
    for (int i = 0; i < 5; i++) {
        vector<int> rowHints = getRowHints(i);

        // 행 힌트 출력 (공백으로 구분)
        string hintStr = "";
        if (rowHints.size() == 1 && rowHints[0] == 0) {
            hintStr = "0";
        }
        else {
            for (int k = 0; k < rowHints.size(); k++) {
                hintStr += to_string(rowHints[k]);
                if (k < rowHints.size() - 1) {
                    hintStr += " ";
                }
            }
        }

        // 힌트를 3자리 공간에 우측 정렬
        cout.width(3);
        cout << right << hintStr << "|";

        // 격자 출력
        for (int j = 0; j < 5; j++) {
            if (user_choice[i][j] == 1)
                cout << "■ ";
            else
                cout << "□ ";
        }
        cout << endl;
    }
}

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

vector<int> getRowHints(int row) {
    vector<int> hints;
    int count = 0;

    for (int j = 0; j < 5; j++) {
        if (puzzles[puzzle_index][row][j] == 1) {
            count++;
        }
        else {
            if (count > 0) {
                hints.push_back(count);
                count = 0;
            }
        }
    }
    if (count > 0) {
        hints.push_back(count);
    }

    if (hints.empty()) {
        hints.push_back(0);
    }

    return hints;
}

vector<int> getColHints(int col) {
    vector<int> hints;
    int count = 0;

    for (int i = 0; i < 5; i++) {
        if (puzzles[puzzle_index][i][col] == 1) {
            count++;
        }
        else {
            if (count > 0) {
                hints.push_back(count);
                count = 0;
            }
        }
    }
    if (count > 0) {
        hints.push_back(count);
    }

    if (hints.empty()) {
        hints.push_back(0);
    }

    return hints;
}

void giveHint() {
    if (hint_count <= 0) {
        cout << "힌트를 모두 사용했습니다!" << endl;
        return;
    }

    vector<pair<int, int>> hints;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (puzzles[puzzle_index][i][j] == 1 && user_choice[i][j] == 0) {
                hints.push_back(make_pair(i, j));
            }
        }
    }

    if (hints.empty()) {
        cout << "더 이상 힌트가 없습니다!" << endl;
        return;
    }

    int randomIndex = rand() % hints.size();
    int hintRow = hints[randomIndex].first;
    int hintCol = hints[randomIndex].second;

    char rowChar = 'A' + hintRow;
    char colChar = '1' + hintCol;

    cout << "힌트: " << rowChar << colChar << "는 어떤가요?" << endl;
    hint_count--;
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    cout << "0~9 사이의 퍼즐 번호를 선택하세요: ";
    cin >> puzzle_index;

    string input;
    while (life > 0) {
        printNonogramHints();
        cout << "목숨: " << life << " | 힌트 남은 횟수: " << hint_count << " | 칸 선택 예: A1, 힌트: hint" << endl;
        cin >> input;

        if (input == "hint" || input == "HINT") {
            giveHint();
            continue;
        }

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

    if (life <= 0) {
        cout << "GAME OVER\n" << "정답 : \n";
        printPuzzle(puzzles[puzzle_index]);
    }

    return 0;
}
