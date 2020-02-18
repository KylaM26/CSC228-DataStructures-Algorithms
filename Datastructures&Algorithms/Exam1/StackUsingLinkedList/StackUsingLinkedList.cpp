
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

class Stack{

    private:
        Node *headPtr;
    
    public:
        Stack(){
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
        
    
        
        void push(int data){
            // Implement the push function directly without calling any other function
            Node* newNode = new Node();
            newNode->setData(data);
            
            if(isEmpty()) {
                headPtr->setNextNodePtr(newNode);
                newNode->setNextNodePtr(nullptr);
            } else {
                Node* followingNode = headPtr->getNextNodePtr();
                headPtr->setNextNodePtr(newNode);
                newNode->setNextNodePtr(followingNode);
            }
        }
        
        
        int peek(){
            
            // Implement the peek function directly without calling any other function
            return isEmpty() ? -100000 : headPtr->getNextNodePtr()->getData();
            
            
        }
        
    
        int pop(){
            
            // Implement the pop function directly without calling any other function
            Node* popNode = isEmpty() ? nullptr : headPtr->getNextNodePtr();

            if(popNode) {
                Node* nextNode = popNode->getNextNodePtr();
                headPtr->setNextNodePtr(nextNode);
                return popNode->getData();
            }
            
            return -10000;
        }

        
        
};

int main(){

    int StackSize;
    cout << "Enter the number of elements you want to push: ";
    cin >> StackSize;
    
    int maxValue;
    cout << "Enter the max. value: ";
    cin >> maxValue;

    int numTrials;
    cout << "Enter the number of trials: ";
    cin >> numTrials;

    
    srand(time(NULL));
    

    
    //cout << "Integers pushed to the Stack: ";
    
    using namespace std::chrono;

    double totalPushingTime = 0;
    double totalPoppingTime = 0;
    
    
  for (int trials = 1; trials <= numTrials; trials++){
      
    Stack integerStack; // Create an empty stack
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int i = 0; i < StackSize; i++){
        int value = 1 + rand() % maxValue;
        integerStack.push(value);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double, std::micro> pushingTime_micro = t2 - t1;
    totalPushingTime += pushingTime_micro.count();
    

    
    t1 = high_resolution_clock::now();
    while (!integerStack.isEmpty())
        integerStack.pop();
    
    t2 = high_resolution_clock::now();
    duration<double, std::micro> poppingTime_micro = t2 - t1;
    totalPoppingTime += poppingTime_micro.count();
    
  }// trials
  
    cout << "Avg. Pushing time (microseconds): " << (totalPushingTime/numTrials) << endl;
    cout << "Avg. Popping time (microseconds): " << (totalPoppingTime/numTrials) << endl;

    system("pause");
    
    //cout << endl;
    
    
return 0;
}
