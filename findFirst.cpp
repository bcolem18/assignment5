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



int minPos(int arr[],int i, int N, int val)
{
   
    int pos=N+1; 
    if(arr[i]==val)
    {
      /*  if(i<pos)
        {
            pos=i; 
        } */
        
        return i; 
    }
   
    else
    {
         int pos1; 
         int pos2; 
        #pragma omp task shared(pos1)
        pos1=minPos(arr,i, N/2,val); 
        
        #pragma omp task shared(pos2)
        pos2=minPos(arr,i+(N/2),N-(N/2),val); 
        
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
         x= minPos(arr, 0, N,val); 
         //x=oPos(val, N); 
        
        
    }
    
    
    
    //return min;
    
   std::cout<<x<<std::endl; 
    
    
    
    
}