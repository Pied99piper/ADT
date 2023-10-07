#include<math.h>
#include<stdio.h>
#include<stdlib.h>

void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void insertionSort(int arr[], int size)
{
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        printArray(arr,size);
    }
}

int main(){
    int size,i,n;
    int *arr;
    scanf("%d",&size);
    arr = (int*)malloc(sizeof(int)*size);
    for (i = 0 ; i < size ; i++){
        scanf("%d", &n);
        arr[i] = n;
    }
    // printArray(arr,size);
    insertionSort(arr,size);
}