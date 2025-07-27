#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Nonogram {
private:
    int ROWS, COLS;
    int** solution;

public:
    Nonogram(int rows, int cols);
    ~Nonogram();
    void RandomSolution();
    void printSolution(); // 확인용 출력 함수
};

Nonogram::Nonogram(int rows, int cols)
    : ROWS(rows), COLS(cols)   //바로 맴버 변수 초기화할 수 있는  방법 
{
    // 2차원 배열 
    solution = new int *[ROWS];
    for (int i = 0; i < ROWS; ++i) {
        solution[i] = new int[COLS];
    }
}

Nonogram::~Nonogram() {  // 소멸자 <--따로 해줘야한다는데 자동으로 되지 않나..?
    // 동적 할당 해제
    for (int i = 0; i < ROWS; ++i) {
        delete[] solution[i];
    }
    delete[] solution;
}

void Nonogram::RandomSolution() {
    srand((unsigned int)time(0)); // 시드 초기화
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            solution[r][c] = rand() % 2;  // 0 또는 1 난수 생성
        }
    }
}

void Nonogram::printSolution() {
    cout << "정답 퍼즐 (0=빈칸, 1=채움):\n";
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            cout << solution[r][c] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    Nonogram game(5, 5);  // 5x5 퍼즐 생성
    game.RandomSolution();
    game.printSolution();
    return 0;
}
