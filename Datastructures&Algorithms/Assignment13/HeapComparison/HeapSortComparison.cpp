#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;


void rearrangeHeapArray(int *array, int arraySize, int index){
    
        // Getting children nodes
        int leftChildIndex = 2*index + 1;
        int rightChildIndex = 2*index + 2;
        
        // If left child is out of index?
        if (leftChildIndex >= arraySize)
            return;
        
        
        if (rightChildIndex >= arraySize){ // Right child is out of bounds
            
            // In this case I should test if it is less???
            if (array[index] > array[leftChildIndex]){ // If leftchild is greater than current index
                int temp = array[index]; // Storing the index value
                array[index] = array[leftChildIndex]; // swaping with the index
                array[leftChildIndex] = temp;
            }
            
            return; // Return out of function
        }
        
        
        // Leave out of the function if array at index greater than left child and right child
        // In case of min heap leave out if both are less???
        if (array[index] <= array[leftChildIndex] && array[index] <=  array[rightChildIndex])
            return;
        
        // Assuming max index will be left child index
        int maxIndex = leftChildIndex;
        
        // If child on the left is less than right, set the max
        if (array[leftChildIndex] > array[rightChildIndex])
            maxIndex = rightChildIndex;
        
        // Swapping left child with right child.
        int temp = array[maxIndex];
        array[maxIndex] = array[index];
        array[index] = temp;
        
        // Rearrange heap
        rearrangeHeapArray(array, arraySize, maxIndex);
}


int main(){
    
    int arraySize;
    
    cout << "Enter array size: ";
    cin >> arraySize;
    
    int *array = new int[arraySize];

    int maxValue;
    cout << "Enter the max. value for any element: ";
    cin >> maxValue;
    
    srand(time(NULL));
    
    // cout << "Generated array: ";
    for (int i = 0; i < arraySize; i++){
        //cout << "Enter element at index " << i << " : ";
        //cin >> array[i];
        array[i] = rand() % maxValue;
      //  cout << array[i] << " ";
    }
    
    cout << endl;
    
    
    //max. heap construction
    for (int index = (arraySize/2)-1; index  >= 0; index--){
        rearrangeHeapArray(array, arraySize, index);
            
    }
    

    cout << "After Heap construction..." << endl;
    for (int index = 0; index < arraySize; index++)
        cout  << array[index] << " ";
    
    cout << endl;
    
    
    
    // Heap sort
    
    for (int iterationIndex = 0; iterationIndex < arraySize; iterationIndex++){
        
        int temp = array[0];
        array[0] = array[arraySize-1-iterationIndex];
        array[arraySize-1-iterationIndex] = temp;
        
        rearrangeHeapArray(array, arraySize-1-iterationIndex, 0);
        
        cout << "Iteration " << iterationIndex << " : ";
        for (int index = 0; index < arraySize; index++)
            cout << array[index] << " ";
        
        cout << endl;
        
    }
    
    cout << "After heap sort...";
    for (int index = 0; index < arraySize; index++)
        cout << array[index] << " ";
    
    // End it here
    
    cout << endl;
    
    system("pause");
    
    return 0;
}
