#include <iostream>
#include <fstream> // 텍스트 파일 읽기
#include <cctype>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include "Print.h"  

using namespace std;

int score = 0;
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
void checkPlayer(string& name, int& orii_score, string player_name) {
    ifstream file("RANK.txt"); // 파일 열기
    if (!file.is_open()) {
        cout << "파일을 열 수 없습니다." << endl;
        return;
    }
    vector<string> names;
    vector<int> scores;

    string linee;
    while (getline(file, linee)) {
        size_t pos = linee.find('-');
        if (pos != string::npos) {
            string name1 = linee.substr(0, pos);
            string scoreStr = linee.substr(pos + 1);

            int orii_score = stoi(scoreStr);

            names.push_back(name1);
            scores.push_back(orii_score);
            // 테스트 출력
            // cout << "이름: " << name << ", 점수: " << ori_score << endl;
        }
    }
    int temp_count = -1;
    for (const string& n : names) {
        temp_count++;
        if (n == player_name) {
            cout << "플레이어 " << n << "의 기록을 찾았습니다.\n";
            name = n; // 기존 이름으로 설정
            orii_score = scores[temp_count];
        }
    }
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
    Print hint;

    string player_name;
    bool player_exists = false;

    cout << "플레이어 이름을 입력하세요: ";
    getline(cin, player_name);

    string ori_name;
    int orii_score = 0;
    checkPlayer(ori_name, orii_score, player_name);

    if (player_name == ori_name) {
        player_exists = true;
        cout << "이전 기록이 있습니다 이어서 진행하시겠습니까? (Y/N): ";
        string choice;
        cin >> choice;
        cin.ignore();
        if (choice == "Y" || choice == "y") {
            score = orii_score;
            cout << "이전 점수: " << score << endl;
        }
        else {
            score = 0; // 새 게임 시작
            cout << "새 게임을 시작합니다.\n";
        }

    }



    cout << "게임 방법: 힌트를 보고 빈칸을 채우기\n";
    cout << "칸 선택 예시 : A1" << endl;

    bool playAgain = true;
    while (playAgain) {

        // 초기화
        life = 3;
        hint_count = 3;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                user_choice[i][j] = 0;


        cout << "0~9 사이의 퍼즐 번호를 선택하세요: ";
        cin >> puzzle_index;
        cout << "Hint: " << puzzle_name[puzzle_index] << endl;
        cin.ignore();

        string input_num;
        bool skip_puzzle = false;

        while (life > 0) {
            if (!skip_puzzle) {
                hint.printHint(puzzles[puzzle_index], user_choice);
            }
            skip_puzzle = false;

            cout << "목숨: " << life << " || 현재점수:" << score << " || 보유힌트:" << hint_count << endl;
            cout << "좌표 선택: \n";

            getline(cin, input_num);
            stringstream stream(input_num);
            bool cor = false;
            bool wro = false;
            int cor_count = 0;
            int wro_count = 0;
            vector<string> incor_temp;
            vector<string> cor_temp;

            while (stream >> input_num) {
                if (input_num.length() != 2) {
                    cout << "입력이 잘못되었습니다." << endl;
                    continue;
                }

                int row = alphatonum(input_num[0]);
                int col = input_num[1] - '1';

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
                    cor_temp.push_back(input_num);
                    cor_count++;
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
                cin.ignore();

                if (choice == "Y" || choice == "y") {
                    if (hint_count > 0) {
                        cout << "\n힌트를 사용하셨습니다!\n\n(남은 힌트: " << --hint_count << "개)";
                        life++;
                        if (!cor_temp.empty()) {
                            srand(static_cast<unsigned int>(time(0)));
                            size_t randomIndex = rand() % cor_temp.size();
                            cout << "\n---------------\n";
                            cout << "힌트 - 맞는 좌표 중 하나: ";
                            cout << cor_temp[randomIndex] << "\n";
                        }
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
                    int row = alphatonum(cor_temp[i][0]);
                    int col = cor_temp[i][1] - '1';
                    user_choice[row][col] = 0;
                }
                skip_puzzle = true;
                continue;
            }

            if (cor || wro) {
                cout << "\n---------------\n";
                if (cor) {
                    cout << "  정답입니다!\n";
                    score += cor_count;
                    cout << "맞는 좌표: ";
                    for (const auto& val : cor_temp)
                        cout << val << " ";
                    cout << "\n\n";
                }
                if (wro) {
                    cout << wro_count << "개 틀렸으므로 목숨이 " << wro_count << "개 차감되었습니다!\n";
                    cout << "틀린 좌표: ";
                    score -= wro_count;
                    for (const auto& val : incor_temp)
                        cout << val << " ";
                    cout << "\n\n";
                }
                cout << "---------------\n";
            }

            bool Finished = true;
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    if (puzzles[puzzle_index][i][j] == 1 && user_choice[i][j] == 0)
                        Finished = false;

            if (Finished) {
                cout << "\n최종 결과:\n";
                printPuzzle(user_choice);
                cout << "\n" << player_name << "님 축하합니다! 퍼즐을 완성했습니다!\n";
                break;
            }
        }

        if (life <= 0) {
            cout << "GAME OVER\n" << "정답 : \n";
            printPuzzle(puzzles[puzzle_index]);
        }

        if (player_exists) {
            ifstream infile("RANK.txt");
            ofstream tempFile("TEMP.txt"); // 임시 파일
            cout << player_name << "의 최종 점수: " << score << endl;
            string lineee;
            while (getline(infile, lineee)) {
                if (lineee.find(player_name + "-") == 0) {
                    // 이름으로 시작하는 줄을 찾아서 새 점수로 덮어씀
                    tempFile << player_name << "-" << score << endl;
                    player_exists = true;
                }
                else {
                    // 그대로 복사
                    tempFile << lineee << endl;
                }
            }

            tempFile.close();
            infile.close();

            remove("RANK.txt");
            rename("TEMP.txt", "RANK.txt");

        }
        else {
            ofstream file("RANK.txt", ios::app);  // ios::app 옵션으로 append 모드로 열기
            if (file.is_open()) {
                cout << player_name << "의 최종 점수: " << score << endl;
                file << player_name << "-" << score << endl;  // << endl 로 줄 바꿈 추가
                file.close();
            }
            else {
                cout << "error" << endl;
                return 1;
            }
        }



        cout << "\n게임을 다시 시작하시겠습니까? (Y/N): ";
        string again;
        cin >> again;
        cin.ignore();
        if (again != "Y" && again != "y")
            playAgain = false;
    }

    cout << "게임을 종료합니다.\n";
    return 0;
}
