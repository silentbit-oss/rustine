void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}


/*** DEPENDENCIES:
***/


int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j <= (high - 1); j += 1)
  {
    if (arr[j] <= pivot)
    {
      i += 1;
      swap(&arr[i], &arr[j]);
    }
  }

  swap(&arr[i + 1], &arr[high]);
  return i + 1;
}


/*** DEPENDENCIES:
void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}


----------------------------
***/


void quickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    int i = partition(arr, low, high);
    quickSort(arr, low, i - 1);
    quickSort(arr, i + 1, high);
  }
}


/*** DEPENDENCIES:
int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j <= (high - 1); j += 1)
  {
    if (arr[j] <= pivot)
    {
      i += 1;
      swap(&arr[i], &arr[j]);
    }
  }

  swap(&arr[i + 1], &arr[high]);
  return i + 1;
}


----------------------------
***/


