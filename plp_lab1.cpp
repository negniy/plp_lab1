#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;

void read_matrix(string filename, vector<vector<int>>& A) {
    ifstream f(filename);
    if (f.is_open()) {
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A[i].size(); j++) {
                f >> A[i][j];
            }
        }
    }
    f.close();
}

vector<vector<int>> mul_matrix(vector<vector<int>> A, vector<vector<int>> B) {
    int N = A.size();
    vector<vector<int>> C(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

void write_matrix(string filename, vector<vector<int>>& A) {
    ofstream f(filename);
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            f << A[i][j] << "\n";
        }
    }
    f.close();
}


int main()
{
    setlocale(LC_ALL, "Russian");

    int list_of_size[8]{ 10, 20, 50, 100, 200, 500, 750, 1000 };


    string res_filename, filename1, filename2;
    string filename[3]{ "C:\\Users\\dstep\\source\\repos\\plp_lab1\\matrix_A",
        "C:\\Users\\dstep\\source\\repos\\plp_lab1\\matrix_B",
        "C:\\Users\\dstep\\source\\repos\\plp_lab1\\matrix_C" };

    for(int size: list_of_size)
    {
        vector<vector<int>> A(size, vector<int>(size));
        vector<vector<int>> B(size, vector<int>(size));

        filename1 = filename[0];
        filename2 = filename[1];
        read_matrix(filename1.append(to_string(size)).append(".txt"), A);
        read_matrix(filename2.append(to_string(size)).append(".txt"), B);

        auto start = chrono::steady_clock::now();
        vector<vector<int>> C = mul_matrix(A, B);
        auto end = chrono::steady_clock::now();

        res_filename = filename[2];
        write_matrix(res_filename.append(to_string(size)).append(".txt"), C);

        ofstream result("time_result.txt", ios::app);
        result << "Размер матрицы: " << size << "х" << size << " Время: " << chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
        result.close();

        cout << "Diff(ms) = " << chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
    }

    return 0;
}
