#include <iostream>
#include <vector>
#include <Windows.h>
#include <mutex>
#include <thread>

using namespace std;

const int N = 16; 
const int THREADS = 4;
int totalSolutions = 0;
mutex mtx;

// Checks if the field is safe to place a queen
bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

// Recursively solves the problem
void solveNQueens(vector<int>& board, int row, int& solutions) {
    if (row == N) { // Solution found
        solutions++;
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveNQueens(board, row + 1, solutions);
            board[row] = -1; // Backtrack to reset board
        }
    }
}

// Function for each thread (handles multiple starting columns)
void threadFunction(int startCol, int step) {
    int localSolutions = 0;

    for (int col = startCol; col < N; col += step) { // Spread work among threads
        vector<int> board(N, -1);
        board[0] = col;
        solveNQueens(board, 1, localSolutions);
    }

    lock_guard<mutex> lock(mtx);
    totalSolutions += localSolutions;
}

int main() {
    LARGE_INTEGER frequency, start, end;
    vector<int> board(N, -1);
    int solutions = 0;
    double duration;

    // Sequential Execution
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    solveNQueens(board, 0, solutions);
    QueryPerformanceCounter(&end);

    cout << "Number of solutions for " << N << "-queens (sequential): " << solutions << endl;
    duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
    wcout << "Sequential runtime: " << duration << " ms" << endl;
    wcout << "Sequential runtime: " << static_cast<int>(duration) / 60000 << " min " << (static_cast<int>(duration) % 60000) / 1000 << " s" << endl;


   

    vector<thread> threads;

    // Multithreaded Execution
    QueryPerformanceCounter(&start);
    for (int i = 0; i < THREADS; i++) {
        threads.emplace_back(threadFunction, i, THREADS);
    }
    for (auto& t : threads) {
        t.join();
    }
    QueryPerformanceCounter(&end);
    
    cout << "Number of solutions for " << N << "-queens (threaded): " << totalSolutions << endl;
    duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
    wcout << "Threaded runtime: " << duration << " ms" << endl;



    return 0;
}
