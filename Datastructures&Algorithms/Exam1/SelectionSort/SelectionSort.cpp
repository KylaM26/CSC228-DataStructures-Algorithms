
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <time.h>
#include <stdlib.h>

using namespace std;

// implementing the dynamic List ADT using array
// operations to be implemented: read, Modify, delete, isEmpty, insert, countElements

class List{

    private:
        int *array;
        int maxSize; // useful to decide if resizing (doubling the array size) is needed
        int endOfArray;
    
    public:
        List(int size){
            array = new int[size];
            maxSize = size;
            endOfArray = -1;
        }
        
        void deleteList(){
            delete[] array;
        }
        
        bool isEmpty(){
            
            if (endOfArray == -1)
                return true;
            
            return false;
        }
        
        void resize(int s){
            
            int *tempArray = array;
            
            array = new int[s];
            
            for (int index = 0; index < min(s, endOfArray+1); index++){
                array[index] = tempArray[index];
            }
            
            maxSize = s;
            
        }
    
        
        void insert(int data){
            
            if (endOfArray == maxSize-1)
                resize(2*maxSize);
            
            array[++endOfArray] = data;
            
        }
        
        
        void insertAtIndex(int insertIndex, int data){
            
            // if the user enters an invalid insertIndex, the element is
            // appended to the array, after the current last element
            if (insertIndex > endOfArray+1)
                insertIndex = endOfArray+1;
            
            if (endOfArray == maxSize-1)
                resize(2*maxSize);
            
            for (int index = endOfArray; index >= insertIndex; index--)
                array[index+1] = array[index];
            
            array[insertIndex] = data;
            endOfArray++;
            
        }
        
        
        int read(int index){
            return array[index];
        }
        
        void modifyElement(int index, int data){
            array[index] = data;
        }
            
        
        void deleteElement(int deleteIndex){
            
            // shift elements one cell to the left starting from deleteIndex+1 to endOfArray-1
            // i.e., move element at deleteIndex + 1 to deleteIndex and so on
            
            for (int index = deleteIndex; index < endOfArray; index++)
                array[index] = array[index+1];
            
            endOfArray--;
        
        }
        
        int countList(){
            int count = 0;
            for (int index = 0; index <= endOfArray; index++)
                count++;
            
            return count;
        }
        
        void print(){
            
            for (int index = 0; index <= endOfArray; index++)
                cout << array[index] << " ";
            
            cout << endl;
            
        }
    
    void Swap(int i, int j) {
        int a = array[i];
        int b = array[j];
        array[i] = b;
        array[j] = a;
    }
    

};


void SelectionSort(List list){
    
     // Implement the algorithm here for a dynamic array-based implementation of List
    for(int i = 0; i < list.countList() - 2; i++) {
        int min = i;
        
        for(int j = i + 1; j < list.countList() - 1; j++)
            if(list.read(j) < list.read(min)) min = j;
           
        list.Swap(i, min);
    }
}


int main(){

    using namespace std::chrono;
    
    srand(time(NULL));

    int maxValue;
    cout << "Enter the max value: ";
    cin >> maxValue;
    
    int numTrials;
    cout << "Enter the number of trials: ";
    cin >> numTrials;



 for (int listSize = 1000; listSize <= 20000; listSize += 1000){

  double totalSortingTime = 0;
    
  for (int trials = 1; trials <= numTrials; trials++){
    
    List integerList(1);
    
    for (int i = 0; i < listSize; i++){
        
        int value = 1 + rand() % maxValue;
        integerList.insertAtIndex(i, value);
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    SelectionSort(integerList);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    
    duration<double, std::milli> sortingTime_milli = t2 - t1;
    totalSortingTime += sortingTime_milli.count();
    
    integerList.deleteList();
    
  }
    
    
    cout << "Average sorting time for list size " << listSize << " is " << (totalSortingTime/numTrials) << " milli seconds " << endl;

 } // list size    loop
 
    system("pause");
    
return 0;
}
