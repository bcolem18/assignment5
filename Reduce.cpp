#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <iterator>
#include <time.h>
#include <chrono>
#include<ctime>
using namespace std;

int findMin(int arr[], int low, int high)
{
    if(high - low > 1000)
    {
   
        int lmin; 
        int rmin;
        int mid = low + high / 2;
        #pragma omp task shared(lmin, mid)
         lmin= findMin(arr, low, mid); 
        
        #pragma omp task shared(rmin, mid)
        rmin= findMin(arr, mid+1, high); 
        
        #pragma omp taskwait
        return min(lmin, rmin); 
        
    } else {
        // stop spawing and find the
        // minuimum
        int minimum = 2000000000;
        for(int i = low; i <= high; i++) {
            minimum = std::min(minimum, arr[i]);
        }
        return minimum;
    }
}

int min(int lmin, int rmin)
{
    
    if(lmin<rmin)
        {
            return lmin; 
        }
    else
    {
        return rmin; 
    }
}



int main(int argc, char *argv[])
{
    if(argc==2)
    
    {
    
        srand(time(NULL)); 
 
  int N= atof(argv[1]);
 int *arr= new int[N]; 
 
 
  
 
 
  for(int i=0; i<N; i++)
 {
     
     arr[i]= (rand()%10000)+1; 
    
    
     

     
     
     
     
 } //generate array
    
    //int arr[19]= {1,2,1,4,5,5,5,5,5,7,0,7,7,8,9,10,11,12,55};
    
   // int N= 19; 
    int min; 
    omp_set_num_threads(16); 
   // omp_set_schedule(omp_sched_dynamic, 1000);
    #pragma omp parallel 
    {
        
        #pragma omp single
          min= findMin(arr, 0, N-1); 
        
        
    }
    
    
    
    //return min;
    
   std::cout<<min<<std::endl; 
    
    
    }
    
}