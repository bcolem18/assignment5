#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <iterator>
#include <time.h>
#include <chrono>
#include <ctime>
#include <mutex>
using namespace std;


void merge(int arr[], int l, int m, int r)
{
    int i, j, k; 
    
    int n1=m-l+1; 
    int n2=r-m; 
    
    int L[n1]; 
    int R[n2]; 
    
    for(i=0;i<n1; i++)
        L[i]=arr[l+i]; 
        
        for(j=0; j<n2;j++)
            R[j]=arr[m+1+j]; 

    i=0; 
    j=0; 
    k=l; 
    
                while(i<n1 && j<n2)
                    {
                            if(L[i]<=R[j])
                                {
                                    arr[k]=L[i]; 
                                    i++; 
                                        
                                }
                                else
                                    {
                                        
                                        arr[k]=R[j]; 
                                        j++; 
                                        
                                    }
                        
                            k++; 
                        
                    }
            
    
            while(i<n1)
                {
                    arr[k]= R[i]; 
                    j++; 
                    k++; 
                    
                }
                
            while(j<n2)
            {
                arr[k]=R[j]; 
                j++; 
                k++; 
                
            }
    
}

void mergeSort(int arr[], int l, int r)
        {
            if(l<r)
                {
                    int m=l+ (r-l)/2; 
                    
                    #pragma omp task
                        mergeSort(arr,l,m); 
                    
                    #pragma omp task 
                        mergeSort(arr,m+1,r); 
                    
                    #pragma omp taskwait
                        merge(arr,l,m,r); 
                }
            
            
        }
        
        
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
        
int main()
{
    
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size=6; 
    
    
    
     #pragma omp parallel 
    {
        
        #pragma omp single
          
         mergeSort(arr, 0, size - 1);
        
    }
   
 printArray(arr, size);   
    return 0; 
    
    
    
    
    
    
    
}