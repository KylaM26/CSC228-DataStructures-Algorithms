
#include <iostream>
#include <stdlib.h>
#include <time.h>
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
            
        
        void deleteElement(int deleteIndex){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            Node* nextNodePtr = headPtr;
            int index = 0;
            
            while (currentNodePtr != 0){
            
                if (index == deleteIndex){
                    nextNodePtr = currentNodePtr->getNextNodePtr();
                    break;
                }
                
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
                
                index++;
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

    bool isUnique() {
        if(isEmpty()) return false;
        
        //Node* currentNode = headPtr->getNextNodePtr()->getNextNodePtr(); // Current node
        Node* checkNode = headPtr->getNextNodePtr(); // The node that will be check against current node.
        Node* currentNode = checkNode->getNextNodePtr();
        
        
        while(checkNode && currentNode) {
            
                if(checkNode != currentNode) {
                    
                    if(currentNode->getData() == checkNode->getData()) {
                        return false;
                    }
                }
            
            
            if(!currentNode->getNextNodePtr()) {
                checkNode = checkNode->getNextNodePtr();
                currentNode = checkNode->getNextNodePtr();
            } else {
                currentNode = currentNode->getNextNodePtr();
            }
        }
        
        return true;
    }
};


int main(){

    srand(time(NULL));

    int listSize;
    cout << "Enter the number of elements you want to insert: ";
    cin >> listSize;


    int maxValue;
    cout << "Enter the max. value for an element in the list: ";
    cin >> maxValue;


    int numTrials = 1000;

    int numUniqueTrials = 0;

  for (int trials = 1; trials <= numTrials; trials++){

    List integerList; // Create an empty list

    for (int i = 0; i < listSize; i++){

        int value = 1 + rand() % maxValue;
        integerList.insertAtIndex(i, value);
    }


    if (integerList.isUnique()){ // You need to implement the isUnique( ) function in the List class
        numUniqueTrials++;
    }


  }// end trials loop


  cout << "Probability for a list to be unique is: " << (((double) numUniqueTrials)/numTrials) << endl;

    system("pause");

return 0;
}

//int main(){
//
//    srand(time(NULL));
//
//    int listSize;
//    cout << "Enter the number of elements you want to insert: ";
//    cin >> listSize;
//
//
//    int maxValue;
//    cout << "Enter the max. value for an element in the list: ";
//    cin >> maxValue;
//
//
//    int numTrials = 1000;
//
//    int numUniqueTrials = 0;
//    List integerList;
//
//  for (int trials = 1; trials <= numTrials; trials++){
//
//     // Create an empty list
//
//    for (int i = 0; i < listSize; i++){
//
//        int value = 1 + rand() % maxValue;
//        integerList.insertAtIndex(i, value);
//    }
//
//
//    if (integerList.isUnique()){ // You need to implement the isUnique( ) function in the List class
//        numUniqueTrials++;
//    }
//
//  }// end trials loop
//
//
//    if (integerList.isUnique()){ // You need to implement the isUnique( ) function in the List class
//        std::cout << "Is unique" << std::endl;
//    } else {
//        std::cout << "Is NOT unique" << std::endl;
//    }
//
//
//    integerList.IterativePrint();
//
//  cout << "Probability for a list to be unique is: " << (((double) numUniqueTrials)/numTrials) << endl;
//
//    system("pause");
//
//return 0;
//}


//    bool isUnique() {
//
//        // Implement the function
//        // if reached end of list switch node
//
//        if(isEmpty()) return false;
//
//
//        Node* currentNode = headPtr->getNextNodePtr();
//        Node* checkNode = headPtr->getNextNodePtr()->getNextNodePtr();
//        Node* lastNode = headPtr;
//
//
//        while(currentNode != lastNode) {
//            if(checkNode) {
//                if(checkNode != currentNode) {
//                    if(currentNode->getData() == checkNode->getData()) {
//                        std::cout << "SAME DATA: "<< "Current: " << currentNode->getData() << ", Next: " << checkNode->getData() << std::endl;
//                        return false;
//                    }
//                }
//            }
//
//            if(!currentNode->getNextNodePtr()) {
//                lastNode = currentNode;
//                checkNode = checkNode->getNextNodePtr();
//                currentNode = headPtr->getNextNodePtr();
//            } else {
//                currentNode = currentNode->getNextNodePtr();
//            }
//
//        }
//        return true;
//    }
