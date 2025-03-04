

#include <iostream>
#include <vector>

using namespace std;

const int N = 12;

// Sprawdza, czy można umieścić hetmana w danym miejscu
bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;  // Kolizja w kolumnie lub na przekątnych
        }
    }
    return true;
}

// Funkcja rekurencyjna rozwiązująca problem
void solveNQueens(vector<int>& board, int row, int& solutions) {
    if (row == N) { // Znaleziono poprawne ustawienie
        solutions++;
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col; // Umieszczamy hetmana
            solveNQueens(board, row + 1, solutions);
            board[row] = -1; // Cofnięcie ruchu (backtracking)
        }
    }
}

int main() {
    vector<int> board(N, -1);
    int solutions = 0;

    solveNQueens(board, 0, solutions);

    cout << "Liczba rozwiązań dla " << N << "-hetmanów: " << solutions << endl;

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
