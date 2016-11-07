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

int oPos(int, int);

int minPos(int arr[],int i, int j, int N, int val)
{
    int pos=N+1; 
    if(i == j - 1)
    {
        if(i<pos && arr[i] == val)
        {
            pos=i; 
        }
        
        return pos; 
    }
   
    else
    {
         int pos1; 
         int pos2; 
         int mid = (i + j) / 2;
        #pragma omp task shared(pos1)
        pos1=minPos(arr,i, mid, N, val); 
        
        #pragma omp task shared(pos2)
        pos2=minPos(arr,mid, j, N, val); 
        
        #pragma omp taskwait
        
        return oPos(pos1, pos2); 
        
    }
    
  
    
}
     
int oPos(int pos1, int pos2)
{
    if(pos1<pos2)
    {
        return pos1; 
    }
    else
    {
        return pos2; 
    }
     
}





int main()

{
    

     int arr[19]= {1,2,1,4,5,5,5,5,5,7,0,7,7,8,9,10,11,12,55};
    
    int N= 19;
    int val=7; 
    int x; 
    int pos=N+1; 
    #pragma omp parallel 
    {
        
        #pragma omp single
         x= minPos(arr, 0, N, N, val); 
         //x=oPos(val, N); 
        
        
    }
    
    
    
    //return min;
   std::cout << "Got " << val << " at index: " << x << std::endl;
}