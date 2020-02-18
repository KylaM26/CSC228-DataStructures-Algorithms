//
//  main.swift
//  Case2
//
//  Created by Kyla Wilson on 1/23/20.
//  Copyright © 2020 Kyla Wilson. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <time.h>
#include <stdlib.h>

using namespace std;


class List{

    private:
        int *array;
        int maxSize;
        int endOfArray;
    
    public:
        List(int size){
            maxSize = size;
            array = new int[maxSize];
            endOfArray = -1;
        }
        
        bool isEmpty(){
            
            if (endOfArray == -1)
                return true;
            
            return false;
        }
        
        void resize(int s){
            
            int *tempArray = array;
            
            array = new int[s];
            
            for (int index = 0; index < min(s, maxSize); index++){
                array[index] = tempArray[index];
            }
            
            maxSize = s;
            
        }

    
        void insertAtIndex(int insertIndex, int data){
            
            // if the user enters an invalid insertIndex, the element is
            // appended to the array, after the current last element
            if (insertIndex > endOfArray+1 || insertIndex < 0)
                insertIndex = endOfArray+1;
            
            if (endOfArray == maxSize-1){
                    
                    resize(maxSize + 1); // Modified resize function to be maxSize + 1
                    
            }
            
            for (int index = endOfArray; index >= insertIndex; index--)
                array[index+1] = array[index];
            
            
            array[insertIndex] = data;
            endOfArray++;
            
        }
        
        
        
};

int main(){
    using namespace std::chrono;
    
    srand(time(NULL));
    
    int listSize;
    cout << "Enter list size: ";
    cin >> listSize;
    
    int maxValue;
    cout << "Enter the max value: ";
    cin >> maxValue;
    
    int numTrials;
    cout << "Enter the number of trials: ";
    cin >> numTrials;

    
    double totalInsertionTime = 0;


   for (int trials = 1; trials <= numTrials; trials++){
    
    List integerList(1); // we will set the maxSize to 1 and double it as and when needed
    
    for (int i = 1000; i < listSize; i += 1){ // Range from 1000 --> 10000 increments of 1000
        
        int value = 1 + rand()%maxValue;
        
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        integerList.insertAtIndex(i, value);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
    
        duration<double, std::nano> insertionTime_nano = t2 - t1;
        totalInsertionTime += insertionTime_nano.count();
    
    }
    cout << "Trials: " << trials << endl;
        

   }// trials


    cout << "Avg. Insertion Time per Integer (nanoseconds): " << (totalInsertionTime/(numTrials*listSize)) << endl;

return 0;
}

