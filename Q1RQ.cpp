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
        } while (i <= high && arr[i] <= pivot);
        
        do {
            j--;
            comparisonCount++;
        } while (j >= low && arr[j] > pivot); 
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

int main() {
    srand(time(0)); // Seed for random number generator

    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Array before Sorting:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    randomizedQuickSort(arr, 0, n);

    cout << "Sorted Array:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Number of comparisons: " << comparisonCount << endl;

    return 0;
}
