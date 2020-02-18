#include <iostream>
#include <stdlib.h>
#include <time.h>
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
        
                
        void deleteALLElements(int data){
            
            if(isEmpty()) return;
            
            for(int i = endOfArray + 1; i >= 0; i--) {
                if(data == array[i])
                    deleteElement(i);
            }
            
        }
        
        void deleteElement(int deleteIndex){
            
            // shift elements one cell to the left starting from deleteIndex+1 to endOfArray-1
            // i.e., move element at deleteIndex + 1 to deleteIndex and so on
            
            for (int index = deleteIndex; index < endOfArray; index++)
                array[index] = array[index+1];
            
            endOfArray--;
        
        }
        
        
        void IterativePrint(){
            
            for (int index = 0; index <= endOfArray; index++)
                cout << array[index] << " ";
            
            cout << endl;
            
        }

};

int main(){

    srand(time(NULL));
    
    int listSize;
    cout << "Enter the number of elements in the list: ";
    cin >> listSize;
    
    int maxValue;
    cout << "Enter the maximum value for any element in the list: ";
    cin >> maxValue;
    
    List integerList(1); // we will set the maxSize to 1 and double it as and when needed
    
    for (int i = 0; i < listSize; i++){
        
        int value = 1 + rand()%maxValue;
        integerList.insertAtIndex(i, value);
    }
    
    cout << "Before deletion: " << endl;
    integerList.IterativePrint();
    
    int deleteData;
    cout << "Enter the data to delete: ";
    cin >> deleteData;
    
    integerList.deleteALLElements(deleteData);
    
    
    cout << "Contents of the List (after deletion): ";
    integerList.IterativePrint();
    
    system("pause");
    
    
    
return 0;
}
