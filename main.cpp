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
    void printSolution(); // Ȯ�ο� ��� �Լ�
};

Nonogram::Nonogram(int rows, int cols)
    : ROWS(rows), COLS(cols)   //�ٷ� �ɹ� ���� �ʱ�ȭ�� �� �ִ�  ��� 
{
    // 2���� �迭 
    solution = new int *[ROWS];
    for (int i = 0; i < ROWS; ++i) {
        solution[i] = new int[COLS];
    }
}

Nonogram::~Nonogram() {  // �Ҹ��� <--���� ������Ѵٴµ� �ڵ����� ���� �ʳ�..?
    // ���� �Ҵ� ����
    for (int i = 0; i < ROWS; ++i) {
        delete[] solution[i];
    }
    delete[] solution;
}

void Nonogram::RandomSolution() {
    srand((unsigned int)time(0)); // �õ� �ʱ�ȭ
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            solution[r][c] = rand() % 2;  // 0 �Ǵ� 1 ���� ����
        }
    }
}

void Nonogram::printSolution() {
    cout << "���� ���� (0=��ĭ, 1=ä��):\n";
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            cout << solution[r][c] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    Nonogram game(5, 5);  // 5x5 ���� ����
    game.RandomSolution();
    game.printSolution();
    return 0;
}
