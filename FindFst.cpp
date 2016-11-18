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





int main(int argc, char *argv[])

{
    if(argc==3)
    {

    // int arr[19]= {1,2,1,4,5,5,5,5,5,7,0,7,7,8,9,10,11,12,55};
    
   // int N= 19;
    int val=7; 
    int x; 
  
    
    
            
            srand(time(NULL)); 
 
             int N= atof(argv[1]);
             int *arr= new int[N]; 
             int numThreads= atof(argv[2]); 
              int pos=N+1; 
 
  
 
 
  for(int i=0; i<N; i++)
 {
     
     arr[i]= (rand()%10000)+1; 
    
    }
    
  omp_set_num_threads(numThreads);
  
  	std::chrono::time_point<std::chrono::system_clock> start, end;

start = std::chrono::system_clock::now(); 
    
    #pragma omp parallel 
    {
        
        #pragma omp single
         x= minPos(arr, 0, N, N, val); 
         //x=oPos(val, N); 
        
        
    }
    
      end = std::chrono::system_clock::now();
 std::chrono::duration<double> elapsed_seconds = end-start;
 std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 

  std::cout << "finished acomputation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";  
    
    
    //return min;
   std::cout << "Got " << val << " at index: " << x << std::endl;
   
    }
}