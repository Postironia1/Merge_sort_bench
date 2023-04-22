#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void merge(vector<double>& arr, int l, int m, int r, int& count, int& mem);
void mergeSort(vector<double>& arr, int l, int r, int& count, int depth, int& maxDepth, int& mem);

int main() {
    srand(time(nullptr));

    int n = 1000000;
    vector<double> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = (double)rand() / RAND_MAX; // Generate random numbers
    }

    int count = 0;
    int depth = 0;
    int maxDepth = 0;
    int mem = 0;

    mergeSort(arr, 0, n - 1, count, depth, maxDepth, mem);

    cout << "Number of comparisons: " << count << endl;
    cout << "Maximum recursion depth: " << maxDepth << endl;
    cout << "Additional memory used: " << mem << " bytes" << endl;

    // Best case scenario: already sorted array
    vector<double> bestCase(n);
    for (int i = 0; i < n; i++) {
        bestCase[i] = (double)i / n;
    }

    count = 0;
    depth = 0;
    maxDepth = 0;
    mem = 0;

    mergeSort(bestCase, 0, n - 1, count, depth, maxDepth, mem);

    cout << "Best case scenario:" << endl;
    cout << "Number of comparisons: " << count << endl;
    cout << "Maximum recursion depth: " << maxDepth << endl;
    cout << "Additional memory used: " << mem << " bytes" << endl;

    // Worst case scenario: reverse sorted array
    vector<double> worstCase(n);
    for (int i = 0; i < n; i++) {
        worstCase[i] = (double)(n - i) / n;
    }

    count = 0;
    depth = 0;
    maxDepth = 0;
    mem = 0;

    mergeSort(worstCase, 0, n - 1, count, depth, maxDepth, mem);

    cout << "Worst case scenario:" << endl;
    cout << "Number of comparisons: " << count << endl;
    cout << "Maximum recursion depth: " << maxDepth << endl;
    cout << "Additional memory used: " << mem << " bytes" << endl;

    // Average case scenario: randomly shuffled array
    random_shuffle(arr.begin(), arr.end());

    count = 0;
    depth = 0;
    maxDepth = 0;
    mem = 0;

    mergeSort(arr, 0, n - 1, count, depth, maxDepth, mem);

    cout << "Average case scenario:" << endl;
    cout << "Number of comparisons: " << count << endl;
    cout << "Maximum recursion depth: " << maxDepth << endl;
    cout << "Additional memory used: " << mem << " bytes" << endl;

    return 0;
}

void merge(vector<double>& arr, int l, int m, int r, int& count, int& mem) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary vectors
    vector<double> L(n1);
    vector<double> R(n2);

    // Copy data to temporary vectors
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        mem += sizeof(L[i]); // Track memory usage
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        mem += sizeof(R[j]); // Track memory usage
    }

    // Merge the temporary vectors back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
        // Track comparisons made
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<double>& arr, int l, int r, int& count, int depth, int& maxDepth, int& mem) {
    if (l >= r) {
        return;
    }
    count++; 


    int m = l + (r - l) / 2;
    depth++;

    mergeSort(arr, l, m, count, depth, maxDepth, mem);
    mergeSort(arr, m + 1, r, count, depth, maxDepth, mem);
    merge(arr, l, m, r, count, mem);

    depth--;
    maxDepth = max(maxDepth, depth);
}