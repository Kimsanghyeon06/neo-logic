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

// �Լ� ����
vector<int> getRowHints(int row);
vector<int> getColHints(int col);

void printNonogramHints() {
    // �� ��Ʈ�� ���η� ����ϱ� ���� �ִ� ���� ���ϱ�
    int maxColHintHeight = 0;
    vector<vector<int>> allColHints;
    for (int j = 0; j < 5; j++) {
        vector<int> colHints = getColHints(j);
        allColHints.push_back(colHints);
        if (colHints.size() > maxColHintHeight) {
            maxColHintHeight = colHints.size();
        }
    }

    // �� ��Ʈ�� ���η� ���
    for (int height = maxColHintHeight - 1; height >= 0; height--) {
        cout << "    "; // �� ��Ʈ ����
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

    // ���м�
    cout << "   +";
    for (int j = 0; j < 5; j++) {
        cout << "--";
    }
    cout << endl;

    // �� ��Ʈ�� ���� ���
    for (int i = 0; i < 5; i++) {
        vector<int> rowHints = getRowHints(i);

        // �� ��Ʈ ��� (�������� ����)
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

        // ��Ʈ�� 3�ڸ� ������ ���� ����
        cout.width(3);
        cout << right << hintStr << "|";

        // ���� ���
        for (int j = 0; j < 5; j++) {
            if (user_choice[i][j] == 1)
                cout << "�� ";
            else
                cout << "�� ";
        }
        cout << endl;
    }
}

void printPuzzle(int arr[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (arr[i][j] == 1)
                cout << "�� ";
            else
                cout << "�� ";
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
        cout << "��Ʈ�� ��� ����߽��ϴ�!" << endl;
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
        cout << "�� �̻� ��Ʈ�� �����ϴ�!" << endl;
        return;
    }

    int randomIndex = rand() % hints.size();
    int hintRow = hints[randomIndex].first;
    int hintCol = hints[randomIndex].second;

    char rowChar = 'A' + hintRow;
    char colChar = '1' + hintCol;

    cout << "��Ʈ: " << rowChar << colChar << "�� �����?" << endl;
    hint_count--;
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    cout << "0~9 ������ ���� ��ȣ�� �����ϼ���: ";
    cin >> puzzle_index;

    string input;
    while (life > 0) {
        printNonogramHints();
        cout << "���: " << life << " | ��Ʈ ���� Ƚ��: " << hint_count << " | ĭ ���� ��: A1, ��Ʈ: hint" << endl;
        cin >> input;

        if (input == "hint" || input == "HINT") {
            giveHint();
            continue;
        }

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

    if (life <= 0) {
        cout << "GAME OVER\n" << "���� : \n";
        printPuzzle(puzzles[puzzle_index]);
    }

    return 0;
}
