#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<ctime>
using namespace std;

void bubble(int *a, int n)
{
  for (int i=0; i<n; i++)
  {
    int first = i%2;
    #pragma omp parallel for
    for (int j=first; j<n-1; j+=2)
    {
      if (a[j] > a[j+1])
      {
        swap(a[j], a[j+1]);
      }
    }
  }
}

void swap(int &a, int &b)
{
  int test;
  test = a;
  a = b;
  b = test;
}

int main()
{
  int *a,*b , n =10000;
  
  a = new int[n];
  b = new int[n];

  for(int i=0; i<n;i++)
  {
    a[i] = rand() % 10000;
    b[i] = a[i];
  }
  
  double start = omp_get_wtime();
  for (int i=0; i<n; i++)
  {
    for (int j=0; j<n-1; j++)
    { 
      if (b[j] > b[j+1])
      {
        swap(b[j], b[j+1]);
      }
    }
  }
  
  
  
  double end = omp_get_wtime();

  
  double start1 = omp_get_wtime();
  bubble(a,n);
  double end1 = omp_get_wtime();
  
  for (int i=0 ; i<n;i++)
  {
    cout<<a[i]<<"\t";
    if (i %10 == 0)
    {
      cout<<endl;
    }
  }
  
  cout<<"\nSequntional time "<<(end - start)<<endl;
  
  cout<<"parallel time "<<(end1 - start1)<<endl;
}
