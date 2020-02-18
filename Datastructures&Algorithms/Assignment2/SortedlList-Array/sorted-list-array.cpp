
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

// implementing the dynamic List ADT using array
// operations to be implemented: read, Modify, delete, isEmpty, insert, countElements

class SortedList{

    private:
        int *array;
        int maxSize; // useful to decide if resizing (doubling the array size) is needed
        int endOfArray;
    
    public:
        SortedList(int size){
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
        
    
        
        
        void insertSortedOrder(int data){
            if(endOfArray == -1) { // If array is empty.
                insertAtIndex(0, data); // Insert at first index.
                return;
            }

            for(int i = 0; i < maxSize; i++) { // Loop through the entire array.
                if(i == endOfArray) { // If the index has reached the end of array, this means the data was greater than all the values that were already in the array.
                    insertAtIndex(i + 1, data); // insert it at the next index
                    return; // Return out of function
                }
                
                if(data > array[i]) { // If the data we want to insert is greater than the current index.
                    continue; // continue to loop until we find an element in the array that is greater than the data we want to insert then else block will be excuted.
                } else {
                    insertAtIndex(i, data); 
                    return;
                }
            }
            
        }

    
        
        void print(){
            
            for (int index = 0; index <= endOfArray; index++)
                cout << array[index] << " ";
            
            cout << endl;
            
        }

};

int main(){

    using namespace std::chrono;
    
    int listSize;
    cout << "Enter the number of elements you want to insert: ";
    cin >> listSize;
    
    int maxValue;
    cout << "Enter the maximum value for an element in the list: ";
    cin >> maxValue;
    
    srand(time(NULL));
    
    SortedList integerList(1); // Create an empty list
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int i = 0; i < listSize; i++){
        int value = 1 + rand() % maxValue;
        integerList.insertSortedOrder(value);
    }
    
    integerList.print();
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    
    duration<double, std::nano> insertionTime_nano = t2 - t1;
    cout << "Avg insertion time per element " << (insertionTime_nano.count()/listSize) << endl;
        

    integerList.deleteList();
    
    system("pause");
    
return 0;
}
