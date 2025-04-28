#include<iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;

void marge(int a[], int i1, int j1, int i2, int j2)
{
  int i = i1;
  int j = i2;
  int temp[10000];
  int k = 0;
  
  // Merge the two halves into temp[]
  while (i <= j1 && j <= j2)
  {
    if (a[i] < a[j])
    {
      temp[k++] = a[i++];
    }
    else
    {
      temp[k++] = a[j++];
    }
  }
  
  // Copy remaining elements from the first half (if any)
  while (i <= j1)
  {
    temp[k++] = a[i++];
  }
  
  // Copy remaining elements from the second half (if any)
  while (j <= j2)
  { 
    temp[k++] = a[j++];
  }
  
  // Copy the sorted elements back to the original array
  for (i = i1, j = 0; i <= j2; i++, j++)
  {
    a[i] = temp[j];
  }
}

void margesort(int a[], int i, int j)
{
  int mid;
  if (i < j)
  {
    mid = (i + j) / 2;
    
    #pragma omp parallel sections
    {
      #pragma omp section
      margesort(a, i, mid);
      
      #pragma omp section
      margesort(a, mid + 1, j);
    }
    
    marge(a, i, mid, mid + 1, j);
  }
}

void margeSort_seq(int a[], int i, int j)
{
  int mid;
  if (i < j)
  {
    mid = (i + j) / 2;
    
    margeSort_seq(a, i, mid);
    margeSort_seq(a, mid + 1, j);
    
    marge(a, i, mid, mid + 1, j);
  }
}

int main()
{
  int *a, *b, n = 1000;
  
  a = new int[n];
  b = new int[n];
  
  // Initialize the arrays with random values
  for (int i = 0; i < n; i++)
  {
    a[i] = rand() % 1000;  // Random numbers between 0 and 9
    b[i] = a[i];
  }
  
  // Print the original unsorted array
  cout << "Original array:" << endl;
  for (int i = 0; i < n; i++)
  {
    cout << a[i] << " ";
  }
  cout << endl;
  
  // Timing the parallel merge sort
  double start = omp_get_wtime();
  margesort(a, 0, n - 1);
  double end = omp_get_wtime();
  
  // Timing the sequential merge sort
  double start1 = omp_get_wtime();
  margeSort_seq(b, 0, n - 1);
  double end1 = omp_get_wtime();
  
  // Print the sorted array after parallel merge sort
  cout << "Sorted array (Parallel Merge Sort):" << endl;
  for (int p = 0; p < n; p++)
  {
    cout << a[p] << " ";
  }
  cout << endl;
  
  // Print the sorted array after sequential merge sort
  cout << "Sorted array (Sequential Merge Sort):" << endl;
  for (int p = 0; p < n; p++)
  {
    cout << b[p] << " ";
  }
  cout << endl;
  
  // Print the execution times
  cout << "Time for Parallel Merge Sort: " << (end - start) << " seconds" << endl;
  cout << "Time for Sequential Merge Sort: " << (end1 - start1) << " seconds" << endl;
  
  // Free the allocated memory
  delete[] a;
  delete[] b;

  return 0;
}

