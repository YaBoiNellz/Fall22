#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX_N 10000
int mul_matrix[MAX_N][MAX_N];

int min_multiplications(int *dims, int i, int j) {
    if (i == j)  // single matrix
        return 0;

    if (mul_matrix[i][j] != -1) {  // if minimum multiplications for range [i, j] was already calculated
        return mul_matrix[i][j];
    }

    mul_matrix[i][j] = 2147483647;  // maximum possible value of `int`

    // calculating minimum number of multiplications across all split cases
    for (int k = i; k < j; ++k) {
        mul_matrix[i][j] = min(
                mul_matrix[i][j],
                min_multiplications(dims, i, k)  // minimum multiplications for left split
                + min_multiplications(dims, k + 1, j)  // minimum multiplications for right split
                + dims[i] * dims[k + 1] * dims[j + 1]  // multiplications for multiplying resulting matrices (rows_first * rows_second * cols_second)
        );
    }

    return mul_matrix[i][j];
}

int multiplication_driver(int argc, char **argv) {
    //Please place all functionality in here instead of the main.
    //Feel free to make any functions or objects you wish, as long as we only call this function.
    ifstream dim_file(argv[1]);
    int *dims_ = new int();
    int n = 0;
    string line;
    while (getline(dim_file, line)) {
        if (line.empty()) continue;
        dims_[n++] = stoi(line);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mul_matrix[i][j] = -1;
        }
    }
    cout << min_multiplications(dims_, 0, n - 2) << endl;
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << "<dimensions_file>" << endl;
        return 0;
    }

    multiplication_driver(argc, argv);

    return 0;
}
