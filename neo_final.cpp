#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include "Print.h"  
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
int hint_count = 3;
int input_count = 0; // 입력된 좌표 개수
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

int main() {
    Print hint;  // Hint 클래스 객체 생성

    cout << "0~9 사이의 퍼즐 번호를 선택하세요: ";
    cin >> puzzle_index;
    cout << "Hint:" << puzzle_name[puzzle_index] << endl;
    cin.ignore();

    string input_num;
    bool skip_puzzle = false;
    while (life > 0) {
        if (!skip_puzzle) {
            hint.printHint(puzzles[puzzle_index], user_choice);
        }
        skip_puzzle = false;
        cout << "목숨: " << life << " (칸 선택 예: A1)\n" << endl;
        cout << "좌표 선택: \n";

        getline(cin, input_num);
        stringstream stream(input_num);
        bool cor = false;
        bool wro = false;
        int wro_count = 0;
        vector<string> incor_temp;
        vector<string> cor_temp;

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

            input_count++;
            bool correct = checkAnswer(row, col);
            if (correct) {
                cor = true;
                cor_temp.push_back(input_num);
            }
            else {
                wro = true;
                incor_temp.push_back(input_num);
                wro_count++;
            }
        }
        if (cor && wro) {
            cout << "\n 정답과 오답이 같이 있습니다. 다시 시도하세요.\n";
            cout << "힌트를 보시겠습니다? (y,n)\n";
            string choice;
            cin >> choice;
            if (choice == "Y" || choice == "y") {
                if (hint_count > 0) {
                    cout << "\n힌트를 사용하셨습니다!\n\n(남은 힌트: " << --hint_count << "개)";
                    life++;
                    if (cor && !cor_temp.empty()) {
                        srand(static_cast<unsigned int>(time(0)));
                        size_t randomIndex = rand() % cor_temp.size();
                        cout << "\n---------------\n";
                        cout << "힌트 - 맞는 좌표 중 하나: ";
                        cout << cor_temp[randomIndex] << "\n";
                    }
                    /*
                    if (wro) {
                        cout << "틀린 좌표: ";
                        for (size_t i = 0; i < incor_temp.size(); ++i) {
                            cout << incor_temp[i] << " ";
                        }
                        cout << "\n";
                    }*/
                    cout << "---------------\n";
                }
                else {
                    cout << "---------------------\n";
                    cout << "남은 힌트가 없습니다!\n";
                    cout << "---------------------\n";
                }

            }

            else {
                cout << "\n-------------------\n";
                cout << "힌트를 사용안하셨습니다!";
                cout << "\n-------------------\n";
            }
            for (size_t i = 0; i < cor_temp.size(); ++i) {
                int row = alphatonum(cor_temp[i][0]); // A~E → 0~4
                int col = cor_temp[i][1] - '1'; // 1~5 → 0~4
                user_choice[row][col] = 0;
            }
            skip_puzzle = true;
            continue;
        }

        if (cor || wro) {
            cout << "\n---------------\n";
            if (cor) {
                cout << "  정답입니다!\n";
                cout << "맞는 좌표: ";
                for (size_t i = 0; i < cor_temp.size(); ++i) {
                    cout << cor_temp[i] << " ";
                }
                cout << "\n";
                cout << endl;
            }
            if (wro) {
                cout << wro_count << "개 틀렸으므로 목숨이 " << wro_count << "개 차감되었습니다!\n";
                cout << "틀린 좌표: ";
                for (size_t i = 0; i < incor_temp.size(); ++i) {
                    cout << incor_temp[i] << " ";
                }
                cout << "\n";
                cout << endl;
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