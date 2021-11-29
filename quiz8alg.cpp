/* CPTR 450 Array Sum Alg
  made by Trevor Natiuk & Kaelan Willauer
*/

#include <chrono>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std::chrono;

// Arrays defined globally
const int SIZE_N = 7;
const double ARRAY1[SIZE_N] = {-3, -1.5, -0.7500001, 0, 2.3, 4.9999999, 8.7};
const double ARRAY2[SIZE_N] = {-6,   -1.9999999, -1.9, -0.2500001,
                               1.34, 2.8,        5.6};
const double ARRAY3[SIZE_N] = {-2.2, -0.9, 1.2999999, 1.95, 4.1000001, 5, 7.2};
const double ARRAY4[SIZE_N] = {-8.2, -4.2999999, -3.0000009, -0.05,
                               0.75, 0.9,        7.1};
const double TARGET = 7.7;
const double EPSILON = 0.0000001;


struct solution {
  int ind1;
  int ind2;
  int ind3;
  int ind4;
};

int _boundSearch(const double array[], double targetElement, int lowInd,
                 int highInd, bool upper, int &comparisons) {
  // Base case: 0 elements
  if (lowInd > highInd) {
		return (upper ? std::min(highInd, lowInd) : std::max(highInd, lowInd));
  } else {
    comparisons++;
    // Recursive case: Compare mid to target
    int mid = (lowInd + highInd) / 2;
    double midVal = array[mid];
    if (upper) {
      // If midVal less or equal to target, recurse high
      // Else, recurse low
      if (midVal <= targetElement) {
        return _boundSearch(array, targetElement, mid + 1, highInd, upper,
                            comparisons);
      } else {
        return _boundSearch(array, targetElement, lowInd, mid - 1, upper,
                            comparisons);
      }
    } else {
      // If midVal greater or equal to target, recurse low
      // Else, recurse high
      if (midVal >= targetElement) {
        return _boundSearch(array, targetElement, lowInd, mid - 1, upper,
                            comparisons);
      } else {
        return _boundSearch(array, targetElement, mid + 1, highInd, upper,
                            comparisons);
      }
    }
  }
}

void searchSum(std::vector<solution> &solutions, int &comparisons) {
  // Initialize first, middle, last values of array4
  int ind4 = SIZE_N / 2;
  double arr4low = ARRAY4[0];
  double arr4high = ARRAY4[SIZE_N - 1];
  // Iterative for-loops
  for (int ind1 = 0; ind1 < SIZE_N; ++ind1) {
    for (int ind2 = 0; ind2 < SIZE_N; ++ind2) {
      for (int ind3 = 0; ind3 < SIZE_N; ++ind3) {
        double arr4target =
            TARGET - (ARRAY1[ind1] + ARRAY2[ind2] + ARRAY3[ind3]);
				// Bound search only if target element is within bounds
        if ((arr4target >= arr4low - EPSILON) &&
            (arr4target <= arr4high + EPSILON)) {
          int upBoundIndex = _boundSearch(ARRAY4, arr4target + EPSILON, 0,
                                          SIZE_N - 1, true, comparisons);
          int lowBoundIndex = _boundSearch(ARRAY4, arr4target - EPSILON, 0,
                                           SIZE_N - 1, false, comparisons);
          while (lowBoundIndex <= upBoundIndex) {
            // Write solutions!
            solution newSolution = {ind1, ind2, ind3, lowBoundIndex};
            solutions.push_back(newSolution);
            lowBoundIndex++;
          }
        }
      }
    }
  }
}

int main() {
  int comparisons = 0;
  std::vector<solution> solutions;
  auto begin = high_resolution_clock::now();
  searchSum(solutions, comparisons);
  auto end = high_resolution_clock::now();
  std::cout << "Target: " << TARGET << "\neps: " << EPSILON << "\n\n";
  std::cout << "Solutions: \n";
  for (auto value : solutions) {
    std::cout << std::fixed << std::setprecision(7);
    std::cout << "{" << ARRAY1[value.ind1] << ", ";
    std::cout << ARRAY2[value.ind2] << ", ";
    std::cout << ARRAY3[value.ind3] << ", ";
    std::cout << ARRAY4[value.ind4] << "}" << std::endl;
    std::cout << "Difference: "
              << abs(ARRAY1[value.ind1] + ARRAY2[value.ind2] +
                     ARRAY3[value.ind3] + ARRAY4[value.ind4] - TARGET)
              << "\n";
  }
  std::cout << "\n";
  auto runTime = duration_cast<microseconds>(end - begin);
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Run time: " << runTime.count() << " microseconds." << std::endl;

  return 0;
}