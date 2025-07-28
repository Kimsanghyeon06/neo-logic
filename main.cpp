#include <iostream>
#include <cctype>
#include <string>
using namespace std;

int life = 3;
int puzzles[10][5][5] = {
    {{0,1,0,1,0},{1,1,1,1,1},{1,1,1,1,1},{0,1,1,1,0},{0,0,1,0,0}}, // ��Ʈ
    {{0,0,1,0,0},{0,0,1,0,0},{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0}}, // ���ڰ�
    {{0,1,0,1,0},{0,1,0,1,0},{0,0,0,0,0},{1,0,0,0,1},{0,1,1,1,0}}, // ���¾�
    {{0,0,1,0,0},{0,1,0,1,0},{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0}}, // ���̾Ƹ��
    {{1,1,1,1,1},{1,0,0,0,0},{1,1,1,1,0},{0,0,0,0,1},{1,1,1,1,0}}, // ���� 5
    {{1,1,1,1,1},{0,0,1,0,0},{1,1,1,1,1},{0,1,0,1,0},{1,1,1,1,1}}, // ����ž
    {{0,0,1,0,0},{0,1,1,1,0},{1,0,1,0,1},{0,0,1,0,0},{0,0,1,0,0}}, // �ϰ� ȭ��ǥ
    {{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}}, // T��
    {{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1}}, // �׵θ�
    {{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0},{0,1,0,1,0},{1,0,0,0,1}}  // X��
};

int user_choice[5][5] = { 0 };  // ����ڰ� ���� �Է��ϴ� ����
int puzzle_index = 0; // ������ ���� ��ȣ

void printPuzzle(int arr[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (arr[i][j] == 1)
                cout << "��";
            else
                cout << "��";
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
    cout << "0~9 ������ ���� ��ȣ�� �����ϼ���: ";
    cin >> puzzle_index;

    string input;
    while (life > 0) {
        printPuzzle(user_choice);
        cout << "���: " << life << " | ĭ ���� ��: A1" << endl;
        cin >> input;

        if (input.length() < 2) {
            cout << "�Է��� �߸��Ǿ����ϴ�." << endl;
            continue;
        }

        int row = alphatonum(input[0]); // A~E �� 0~4
        int col = input[1] - '1'; // 1~5 �� 0~4

        if (row < 0 || row >= 5 || col < 0 || col >= 5) {
            cout << "�߸��� ��ġ�Դϴ�." << endl;
            continue;
        }

        if (checkAnswer(row, col)) {
            cout << "�����Դϴ�!\n";
        }
        else {
            cout << "Ʋ�Ƚ��ϴ�. ��� -1\n";
        }

        // �¸� ���� Ȯ��
        bool Finished = true;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (puzzles[puzzle_index][i][j] == 1 && user_choice[i][j] == 0)
                    Finished = false;

        if (Finished) {
            cout << "������ �ϼ��߽��ϴ� \n";
            break;
        }
    }

    if (life <= 0)
        cout << "GAME OVER\n" << "���� : \n", printPuzzle(puzzles[puzzle_index]);

    return 0;
}
