[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9585152&assignment_repo_type=AssignmentRepo)
# Extra Credit Starter Code

# Q1
<hr>

In order to solve this task I used LCS (Longest Common Subsequence) algorithm.  
Because to solve the problem I needed to print subsequence as well,
so I wrote the algorithm for strings and use matrix of subsequences.  
It was challenging to fully understand letters in which index I should use,
because at the first attempt first letter of subsequence had not been included.
After reviewing code I found that `i` and `j` were passed
instead of `i - 1` and `j - 1` respectively. So I fixed it and passed test.

# Q2
<hr>

## optimal_multiplications.cc

For this task I added new function `min_multiplications(int* dims, int i, int j)`  
that calculates the minimum number of multiplications for matrices in range `[i, j]`.
Here `dims` is the array of dimensions from given file, `i` is the index of first matrix
and `j` is the index of last matrix in the range.

Challenging part of this problem was to solve it with less time complexity as my code was
running too slow at the beginning. So I created a global 2D array `mul_matrix` where at
place `i, j` I placed number of minimum multiplications for range `[i, j]` and `-1` if I have
not calculated it yet. As I don't know the upper limit of number of matrices, I have set it to `10 000`.
