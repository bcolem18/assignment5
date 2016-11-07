#include <iostream>

using namespace std;






int minPos(int arr[],int i, int N, int val)
{
    int pos=N+1; 
    
    if(arr[i]==val)
    {
        if(i<pos)
        {
            pos=i; 
        }
        
        return pos; 
    }
    else
    {
         int pos1; 
         int pos2; 
        
        pos1=minPos(arr,i, N,val); 
        
        
       
        
    }
    
    
}

int main()
{
    
     int arr[19]= {1,2,1,4,5,5,5,5,5,7,0,7,7,8,9,10,11,12,55};
    
    int N= 19;
    int val=7; 
    int x; 
    
    x= minPos(arr, 0, N,val);  
    
    std::cout<<x<<std::endl; 
    
    
}