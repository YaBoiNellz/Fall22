#include <iostream>
#include <string>

using namespace std;

int subsequence_driver(int argc, char **argv) {
    //Please place all functionality in here instead of the main.
    //Feel free to make any functions or objects you wish, as long as we only call this function.
    string word_a = argv[1];
    string word_b = argv[2];
    int m = word_a.size();
    int n = word_b.size();
    string common_subsequences[m + 1][n + 1];

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (!i || !j)  // first column or first row
                common_subsequences[i][j] = "";
            else if (word_a[i - 1] == word_b[j - 1])  // letters match
                common_subsequences[i][j] = common_subsequences[i - 1][j - 1] + word_a[i - 1];
            else {  // letters don't match
                string left = common_subsequences[i][j - 1];
                string upper = common_subsequences[i - 1][j];
                if (left.size() > upper.size())
                    common_subsequences[i][j] = left;
                else
                    common_subsequences[i][j] = upper;
            }
        }
    }

    cout << common_subsequences[m][n].size() << endl;
    cout << common_subsequences[m][n] << endl;
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << "<word_a>" << "<word_b>" << endl;
        return 0;
    }

    subsequence_driver(argc, argv);

    return 0;
}
