#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Sorter {
public:
 void mergeSort (int arr[], int l, int r); // recursive
 void quickSort (int arr[], int low, int high); // last-element pivot
 void quickSortM3(int arr[], int low, int high); // median-of-three

private:
 void merge(int arr[], int l, int m, int r);
 int partition (int arr[], int low, int high);
 int partitionM3(int arr[], int low, int high);
 int medianOfThree(int arr[], int low, int high); 

};
void Sorter::merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void Sorter::mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int Sorter::partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Sorter::quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int Sorter::medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;

    // Find the median among arr[low], arr[mid], arr[high]
    if ((arr[low] <= arr[mid] && arr[mid] <= arr[high]) || (arr[high] <= arr[mid] && arr[mid] <= arr[low])) {
        swap(arr[mid], arr[high]);
    } else if ((arr[mid] <= arr[low] && arr[low] <= arr[high]) || (arr[high] <= arr[low] && arr[low] <= arr[mid])) {
        swap(arr[low], arr[high]);
    }

    return high;
}

int Sorter::partitionM3(int arr[], int low, int high) {
    medianOfThree(arr, low, high); // sets pivot at arr[high]
    return partition(arr, low, high);
}

void Sorter::quickSortM3(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionM3(arr, low, high);
        quickSortM3(arr, low, pi - 1);
        quickSortM3(arr, pi + 1, high);
    }
}
int main() {
 Sorter s; int tmp[8];
 int a[] = {64,25,12,22,11,90,45,34}; int n=8;
 // mergeSort
 copy(a,a+n,tmp); s.mergeSort(tmp,0,n-1);
 cout<<"MS: "; for(int x:tmp) cout<<x<<" "; cout<<endl;
 // quickSort
 copy(a,a+n,tmp); s.quickSort(tmp,0,n-1);
 cout<<"QS: "; for(int x:tmp) cout<<x<<" "; cout<<endl;
 // worst-case for quickSort: sorted array
 int sorted[] = {1,2,3,4,5,6,7,8};
 copy(sorted,sorted+n,tmp); s.quickSort(tmp,0,n-1);
 cout<<"QS sorted: "; for(int x:tmp) cout<<x<<" "; cout<<endl;
 // quickSortM3 on same sorted array
 copy(sorted,sorted+n,tmp); s.quickSortM3(tmp,0,n-1);
 cout<<"QSM3 sorted: "; for(int x:tmp) cout<<x<<" "; cout<<endl;
 return 0;
}
