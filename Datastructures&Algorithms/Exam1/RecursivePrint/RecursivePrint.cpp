#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <time.h>
#include <stdlib.h>

using namespace std;

// implementing the dynamic List ADT using Linked List

class Node{
    
    private:
        int data;
        Node* nextNodePtr;
        
    public:
        Node(){}
        
        void setData(int d){
            data = d;
        }
        
        int getData(){
            return data;
        }
        
        void setNextNodePtr(Node* nodePtr){
                nextNodePtr = nodePtr;
        }
        
        Node* getNextNodePtr(){
            return nextNodePtr;
        }
            
};

class List{

    private:
        Node *headPtr;
    
    public:
        List(){
            headPtr = new Node();
            headPtr->setNextNodePtr(0);
        }
    
        Node* getHeadPtr(){
            return headPtr;
        }
    
        bool isEmpty(){
            
            if (headPtr->getNextNodePtr() == 0)
                return true;
            
            return false;
        }
        
        
        void insert(int data){
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            
            while (currentNodePtr != 0){
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
            }
            
            Node* newNodePtr = new Node();
            newNodePtr->setData(data);
            newNodePtr->setNextNodePtr(0);
            prevNodePtr->setNextNodePtr(newNodePtr);
            
        }
        
        void insertAtIndex(int insertIndex, int data){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            
            int index = 0;
            
            while (currentNodePtr != 0){
                
                if (index == insertIndex)
                    break;
                
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
                index++;
            }
            
            Node* newNodePtr = new Node();
            newNodePtr->setData(data);
            newNodePtr->setNextNodePtr(currentNodePtr);
            prevNodePtr->setNextNodePtr(newNodePtr);
            
        }
        
        
        int read(int readIndex){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            int index = 0;
            
            while (currentNodePtr != 0){
            
                if (index == readIndex)
                    return currentNodePtr->getData();
                
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
                
                index++;
                
            }
            
            return -1; // an invalid value indicating
                        // index is out of range
            
        }
        
        void modifyElement(int modifyIndex, int data){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            int index = 0;
            
            while (currentNodePtr != 0){
            
                if (index == modifyIndex){
                    currentNodePtr->setData(data);
                    return;
                }
                
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
                
                index++;
            }
            
            
        }
    
        void deleteElement(int deleteData){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            Node* nextNodePtr = headPtr;
            
            while (currentNodePtr != 0){
            
                if (currentNodePtr->getData() == deleteData){
                    nextNodePtr = currentNodePtr->getNextNodePtr();
                    break;
                }
                
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
                
            }
            
            prevNodePtr->setNextNodePtr(nextNodePtr);
        
        }
        
        
        void IterativePrint(){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            
            while (currentNodePtr != 0){
                cout << currentNodePtr->getData() << " ";
                currentNodePtr = currentNodePtr->getNextNodePtr();
            }
                
            cout << endl;
            
        }


        
        // add the code to the member function
    // RecursivePrintForwardReverseOrders(Node*)
    
    void recursivePrintForwardReverseOrders(Node* firstNode, int printIndex, int size) {
        if(printIndex == size) {
            std::cout << "\n\n";
            return;
        }
        
        std::cout << firstNode->getData() << " ";
        
        if(firstNode) {
            recursivePrintForwardReverseOrders(firstNode->getNextNodePtr(), printIndex + 1, size);
            std::cout << firstNode->getData() << " ";
        }
        
    } 
};

int main(){

    int listSize;
    
    cout << "Enter the number of elements you want to insert: ";
    cin >> listSize;
    
    List integerList; // Create an empty list
    
    srand(time(NULL));
    
    int maxValue;
    
    cout << "Enter the maximum value for an element: ";
    cin >> maxValue;

    
    for (int i = 0; i < listSize; i++){
        int value = rand() % maxValue;
        integerList.insertAtIndex(i, value);
    }
    
    cout << "Contents of the List (IterativePrint): ";
    integerList.IterativePrint();
    
    cout << endl;

    cout << "Contents of the List (Forward and Reverse Orders) " << endl;
    Node* firstNodePtr = integerList.getHeadPtr()->getNextNodePtr();
    int printIndex = 0;
    integerList.recursivePrintForwardReverseOrders(firstNodePtr, printIndex, listSize);
    std:: cout << std::endl;
    return 0;

}
