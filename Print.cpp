#include <iostream>
#include "Print.h"
using namespace std;

void Print::printHint(int puzzle[5][5], int user[5][5]) {
    int col_H[5][3] = { 0 };
    int col_H_Count[5] = { 0 };

    // �� ��Ʈ ���
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

    // �� ��Ʈ ��� (�ִ� 3��)
    for (int line = 0; line < 3; line++) {
        cout << "      "; // �� ��Ʈ ���� Ȯ�� (6ĭ)
        for (int col = 0; col < 5; col++) {
            int hintIndex = col_H_Count[col] - 3 + line;
            if (hintIndex >= 0)
                cout << " " << col_H[col][hintIndex];
            else
                cout << "  ";
        }
        cout << endl;
    }

    // �� ��Ʈ + ���� ���
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

        // �� ��Ʈ ��� (�ִ� 3ĭ ������ ����)
        if (index == 1)
            cout << "    " << row_H[0]; // 4ĭ ���
        else if (index == 2)
            cout << "  " << row_H[0] << " " << row_H[1];
        else
            cout << row_H[0] << " " << row_H[1] << " " << row_H[2];

        cout << "  "; // ���� ��ǥ�� ��Ʈ ���� ����

        // ���� ���
        for (int j = 0; j < 5; j++) {
            if (user[i][j] == 1)
                cout << "�� ";
            else
                cout << "�� ";
        }
        cout << endl;
    }
}
