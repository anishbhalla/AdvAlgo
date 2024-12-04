#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int comparisonCount = 0;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        do {
            i++;
            comparisonCount++;
        } while (i <= high && arr[i] <= pivot); // Corrected condition
        
        do {
            j--;
            comparisonCount++;
        } while (j >= low && arr[j] > pivot); // Corrected condition
        
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[low], arr[j]);
    return j;
}

int randomPartition(vector<int> &arr, int low, int high) {
    int randomPivotIndex = low + rand() % (high - low);
    swap(arr[randomPivotIndex], arr[low]);
    return partition(arr, low, high);
}

void randomizedQuickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int j = randomPartition(arr, low, high);
        randomizedQuickSort(arr, low, j);
        randomizedQuickSort(arr, j + 1, high);
    }
}

int randomizedSelect(vector<int> &arr, int low, int high, int i) {
    if (low == high) {
        return arr[low];
    }

    int pivotIndex = randomPartition(arr, low, high);
    int k = pivotIndex - low + 1; // Position of pivot in sorted order

    if (i == k) { 
        return arr[pivotIndex]; // Found the i-th smallest element
    } else if (i < k) { // Look in the left part
        return randomizedSelect(arr, low, pivotIndex - 1, i);
    } else { // Look in the right part
        return randomizedSelect(arr, pivotIndex + 1, high, i - k);
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    int n, i;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:" << endl;
    for (int j = 0; j < n; j++) {
        cin >> arr[j];
    }

    cout << "Array before Sorting:" << endl;
    for (int j = 0; j < n; j++) {
        cout << arr[j] << " ";
    }
    cout << endl;

    randomizedQuickSort(arr, 0, n);
    cout << "Sorted Array:" << endl;
    for (int j = 0; j < n; j++) {
        cout << arr[j] << " ";
    }
    cout << endl;

    cout << "Number of comparisons during sorting: " << comparisonCount << endl;

    cout << "Enter the position of the smallest element to find (1-based index): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid input. Position must be between 1 and " << n << "." << endl;
        return 1;
    }

    int ithSmallest = randomizedSelect(arr, 0, n - 1, i);
    cout << "The " << i << "-th smallest element is: " << ithSmallest << endl;

    return 0;
}
