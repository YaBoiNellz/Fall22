// Homework 4
// Testing Sorting Algorithms
// Darnell Chambers Gordon

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Computes duration given a start time and a stop time in nano seconds.
// Keep it in.
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time, 
			  chrono::high_resolution_clock::time_point end_time) {
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
    vector <int> rand_array;
    for (size_t i = 0; i < size_of_vector; i++){
        rand_array.push_back(rand());
    }
    return rand_array;
}

// Generates and returns sorted vector of size @size_of_vector.
// If @smaller_to_larger is true, returns vector sorted from small to large.
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
    vector <int> sorted_array;
    int tmp = rand() % 100;
    sorted_array.push_back(tmp);
    for (size_t i = 1; i < size_of_vector; i++){
        if (smaller_to_larger) {
            tmp += (rand() % 3 + 2);
//            tmp += 20;
            sorted_array.push_back(tmp);
        }
        else {
            tmp -= (rand() % 3 + 2);
//            tmp -= 20;
            sorted_array.push_back(tmp);
        }
    }
//    if (smaller_to_larger)
//        for (int i = 0; i < size_of_vector; i++) sorted_array.push_back(i);
//    else
//        for (int i = size_of_vector; i > 0; i--) sorted_array.push_back(i);
    return sorted_array;
}

// Verifies that a vector is sorted given a comparator.
// I.e. it applies less_than() for consecutive pair of elements and returns true
// iff less_than() is true for all pairs.
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {
    if (input.size() == 0)
        return true;
    for (size_t i = 0; i < input.size() - 1; i++){
        if (less_than(input[i + 1], input[i]))
            return false;
    }
    return true;
}

// Functino for testing sorting algorithm
template <typename Comparator>
void Test(vector<int> &arr, void (*sort)(vector<int>&, Comparator), Comparator less_than) {
    cout << "Runtime: ";
    const auto begin_time = chrono::high_resolution_clock::now();
    // Time this piece of code.
    sort(arr, less_than);
    // End of piece of code to time.
    const auto end_time = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin_time, end_time) << " ns" << endl;
    std::cout << "Verified: " << VerifyOrder(arr, less_than) << '\n' << '\n';
}

// Wrapper function to test different sorting algorithms. See homework's PDF for details.
void testSortingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
    cout << "Invalid input type" << endl;
    return;
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    return;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    return;
  }

    std::cout << VerifyOrder(GenerateSortedVector(input_size, 1), less<int>{}) << '\n';


    cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  vector<int> input_vector;
  if (input_type == "random") {
    // Generate random vector @input_vector.
    input_vector = GenerateRandomVector(input_size);
  } else if (input_type == "sorted_small_to_large"){
    // Generate smaller to larger sorted vector @input_vector.
        input_vector = GenerateSortedVector(input_size, true);
  } else{
      // Generate larger to smaller sorted vector @input_vector.
      input_vector = GenerateSortedVector(input_size, false);
  }

  // Call HeapSort / MergeSort / QuickSort  using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // MergeSort(input_vector, less<int>{})
  // otherwise call
  // MergeSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for HeapSort & QuickSort

  vector<int> vec = input_vector;

  if (comparison_type == "less"){
      std::cout << "Heapsort\n";
      Test(input_vector, &heapsort, less<int>{});
      input_vector = vec;
      std::cout << "MergeSort\n";
      Test(input_vector, &mergeSort, less<int>{});
      input_vector = vec;
      std::cout << "QuickSort\n";
      Test(input_vector, &quicksort, less<int>{});
      input_vector = vec;
//      For shellsort
      std::cout << "ShellSort\n";
      Test(input_vector, &shellsort, less<int>{});
      input_vector = vec;
  }else{
      std::cout << "Heapsort\n";
      Test(input_vector, &heapsort, greater<int>{});
      input_vector = vec;
      std::cout << "MergeSort\n";
      Test(input_vector, &mergeSort, greater<int>{});
      input_vector = vec;
      std::cout << "QuickSort\n";
      Test(input_vector, &quicksort, greater<int>{});
      input_vector = vec;
//      For shellsort
      std::cout << "ShellSort\n";
      Test(input_vector, &shellsort, greater<int>{});
      input_vector = vec;
  }

  // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // QuickSort(input_vector, less<int>{})
  // otherwise call
  // QuickSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for QuickSort2 & QuickSort3

    if (comparison_type == "less"){
        std::cout << "Testing Quicksort Pivot Implementations\n\n";
        std::cout << "Median of Three\n";
        Test(input_vector, &QuickSort, less<int>{});
        input_vector = vec;
        std::cout << "Middle\n";
        Test(input_vector, &QuickSort2, less<int>{});
        input_vector = vec;
        std::cout << "First\n";
        Test(input_vector, &QuickSort3, less<int>{});
        input_vector = vec;
    }else{
        std::cout << "Testing Quicksort Pivot Implementations\n\n";
        std::cout << "Median of Three\n";
        Test(input_vector, &QuickSort, greater<int>{});
        input_vector = vec;
        std::cout << "Middle\n";
        Test(input_vector, &QuickSort2, greater<int>{});
        input_vector = vec;
        std::cout << "First\n";
        Test(input_vector, &QuickSort3, greater<int>{});
        input_vector = vec;
    }
}

int main(int argc, char **argv) {
  // DO NOT CHANGE or ADD ANY CODE in this function.
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  
  testSortingWrapper(argc, argv);

  return 0;
}
