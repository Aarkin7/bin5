#include <iostream>
#include <omp.h>
using namespace std;

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int n) {
   #pragma omp parallel for
    for (int i = 0; i < n - 1; i++) {
        
        #pragma omp parallel for 
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
               
            }
            
        }
    }
}

// Merge function for Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

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
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Parallel Merge Sort
void parallelMergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid =  (right + left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }

            #pragma omp section
            {
               
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Parallel Bubble Sort

    double startp = omp_get_wtime();
    parallelBubbleSort(arr, n);
    double endp = omp_get_wtime();

    cout << "Sorted array using Parallel Bubble Sort: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl; 
    cout<<"Time taken: "<<endp - startp<<endl;


    // Parallel Merge Sort
    int ar[] = {12, 11, 13, 3, 6, 7};
    int m = sizeof(ar) / sizeof(ar[0]);

    double startm = omp_get_wtime();
    parallelMergeSort(ar, 0, m - 1);
    double endm = omp_get_wtime();

    cout << "Sorted array using Parallel Merge Sort: ";
    for (int i = 0; i < m; i++) {
        cout << ar[i] << " ";
    }
    cout << endl;

    cout<<"Time taken: "<<endm - startm<<endl;

    return 0;
}


// The #pragma omp parallel sections directive is used in OpenMP to parallelize sections of code. It allows multiple sections of code to be executed in parallel by different threads. Each section is assigned to a separate thread for concurrent execution.