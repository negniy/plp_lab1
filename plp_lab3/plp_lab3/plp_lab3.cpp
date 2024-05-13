#include <mpi.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
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

vector<vector<int>> mul_matrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int N = A.size();
    vector<vector<int>> C(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
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

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    setlocale(LC_ALL, "Russian");

    vector<int> list_of_size{ 10, 20, 50, 100, 200, 500, 750, 1000 };

    string filename1 = "matrix_A.txt";
    string filename2 = "matrix_B.txt";
    string res_filename = "matrix_C.txt";

    for (int size : list_of_size) {
        vector<vector<int>> A(size, vector<int>(size));
        vector<vector<int>> B(size, vector<int>(size));
        vector<vector<int>> C(size, vector<int>(size));

        if (world_rank == 0) {
            read_matrix(filename1, A);
            read_matrix(filename2, B);
        }


        vector<vector<int>> local_C = mul_matrix(A, B);


        if (world_rank == 0) {
            write_matrix(res_filename, C);
        }
    }

    MPI_Finalize();
    return 0;
}
