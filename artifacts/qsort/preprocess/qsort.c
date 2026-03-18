# 0 "/app/subjects/qsort/qsort.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/qsort/qsort.c"
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int i = partition(arr, low, high);
        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, high);
    }
}
