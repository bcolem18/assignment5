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

int findMin(int arr[], int i, int N)
{
    if(N==1)
    {
        return arr[i];
    }
    else
    {
        int lmin; 
        int rmin; 
        #pragma omp task shared(lmin)
         lmin= findMin(arr, i, N/2); 
        
        #pragma omp task shared(rmin)
        rmin= findMin(arr, i+(N/2), N-(N/2)); 
        
        #pragma omp taskwait
        
        return min(lmin, rmin); 
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
          min= findMin(arr, 0, N); 
        
        
    }
    
    
    
    //return min;
    
   std::cout<<min<<std::endl; 
    
    
    }
    
}