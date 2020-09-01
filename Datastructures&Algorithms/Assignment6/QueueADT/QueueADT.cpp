#include <iostream>
#include <stdlib.h> //srand, rand
#include <time.h>//clock_t, clock, CLOCKS_PER_SEC

#include <ctime>
#include <ratio>
#include <chrono>


using namespace std;

// implementing a queue using Stack


class Node{
    
    private:
        int data;
        Node* nextNodePtr;
        Node* prevNodePtr;
        
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
        
        void setPrevNodePtr(Node* nodePtr){
                prevNodePtr = nodePtr;
        }
        
        Node* getPrevNodePtr(){
            return prevNodePtr;
        }
        
};

class Stack{

    private:
        Node* headPtr;
        Node* tailPtr;

    
    public:
        Stack(){
            headPtr = new Node();
            tailPtr = new Node();
            headPtr->setNextNodePtr(0);
            tailPtr->setPrevNodePtr(0);
        }
    
        Node* getHeadPtr(){
            return headPtr;
        }
        
        Node* getTailPtr(){
            return tailPtr;
        }
        
        bool isEmpty(){
            
            if (headPtr->getNextNodePtr() == 0)
                return true;
            
            return false;
        }
        
        
        void push(int data){
            
            Node* newNodePtr = new Node();
            newNodePtr->setData(data);
            newNodePtr->setNextNodePtr(0);
            
            Node* lastNodePtr = tailPtr->getPrevNodePtr();
            
            if (lastNodePtr == 0){
                
                headPtr->setNextNodePtr(newNodePtr);
                newNodePtr->setPrevNodePtr(0);
                
            }
            else{
                
                lastNodePtr->setNextNodePtr(newNodePtr);
                newNodePtr->setPrevNodePtr(lastNodePtr);
                
            }
            
            tailPtr->setPrevNodePtr(newNodePtr);
            
        }

        
        int pop(){
            
            Node* lastNodePtr = tailPtr->getPrevNodePtr();
            Node* prevNodePtr = 0;
            
            int poppedData = -100000; //empty stack
            
            if (lastNodePtr != 0){
                prevNodePtr = lastNodePtr->getPrevNodePtr();
                poppedData = lastNodePtr->getData();
            }
            else
                return poppedData;
            
            if (prevNodePtr != 0){
                prevNodePtr->setNextNodePtr(0);
                tailPtr->setPrevNodePtr(prevNodePtr);
            }
            else{
                headPtr->setNextNodePtr(0);
                tailPtr->setPrevNodePtr(0);
            }

            delete lastNodePtr;
            
            return poppedData;
            
        }

        int peek(){
            
            Node* lastNodePtr = tailPtr->getPrevNodePtr();
            
            if (lastNodePtr != 0)
                return lastNodePtr->getData();
            else
                return -100000; //  empty stack
                
        }

        void IterativePrint(){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            
            while (currentNodePtr != 0){
                cout << currentNodePtr->getData() << " ";
                currentNodePtr = currentNodePtr->getNextNodePtr();
            }
                
            cout << endl;
            
        }

        void ReversePrint(){
            
            Node* currentNodePtr = tailPtr->getPrevNodePtr();
            
            while (currentNodePtr != 0){
                
                cout << currentNodePtr->getData() << " ";
                currentNodePtr = currentNodePtr->getPrevNodePtr();
            }
            
            cout << endl;
        }
    
};


class Queue{
    
private:
    Stack stack1;
    Stack stack2;
    
public:
    Queue(){}
    
    void enqueueCheaper(int data){
        stack1.push(data);
    }
    
    void enqueueCostly(int data){
        int poppedData = stack1.pop();
        
        while(!stack1.isEmpty()) {
            stack2.push(poppedData);
            poppedData = stack1.pop();
        }
        
        stack1.push(data);
        poppedData = stack2.pop();
        
        while(!stack2.isEmpty()) {
            stack1.push(poppedData);
            poppedData = stack2.pop();
        }
    }
    
    int dequeueCheaper(){
        
        return stack1.pop();
        
        
    }

    int dequeueCostly(){
        int poppedData = stack1.pop();
        
        while(!stack1.isEmpty()) {
            stack2.push(poppedData);
            poppedData = stack1.pop();
        }
        
        int temp = stack2.pop();
        poppedData = stack2.pop();
        
        while(!stack2.isEmpty()) {
            stack1.push(poppedData);
            poppedData = stack2.pop();
        }
        
        return temp;
    }

    bool isEmpty(){
        
        // complete the code for the isEmpty function
        
        if (stack1.isEmpty())
            return true;
        return false;
        
    }
    
    
};

int main() {
    using namespace std::chrono;
    
    double totalEnqueuingTime = 0;
    double totalDequeuingTime = 0;
    
    int queueSize;
    
    cout << "Enter the number of elements you want to enqueue: ";
    cin >> queueSize;
    
    srand(time(NULL));
    
    int maxValue;
    
    cout << "Enter the maximum value for an element: ";
    cin >> maxValue;
    
    
    int numTrials;
    cout << "Enter the number of trials: ";
    cin >> numTrials;
    
  cout << "Enqueuing the costly way..." << endl;
    
  for (int trials = 1; trials <= numTrials; trials++){

    Queue EnqueueCostlyQueue; // Create an empty queue
    
    for (int i = 0; i < queueSize; i++){
        
        int value = 1 + rand() % maxValue;
        
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        EnqueueCostlyQueue.enqueueCostly(value);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::micro> enqueueTime_micro = t2 - t1;
        totalEnqueuingTime += enqueueTime_micro.count();
    
    }
    
    
    
    while (!EnqueueCostlyQueue.isEmpty()){
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        EnqueueCostlyQueue.dequeueCheaper();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::micro> dequeueTime_micro = t2 - t1;
        totalDequeuingTime += dequeueTime_micro.count();
        
    }

  }// trials loop
  
  
  cout << "Average Enqueuing Time (micro seconds) " << (totalEnqueuingTime)/(numTrials*queueSize) << endl;
  cout << "Average Dequeuing Time (micro seconds) " << (totalDequeuingTime)/(numTrials*queueSize) << endl;
  

      totalEnqueuingTime = 0;
    totalDequeuingTime = 0;

  cout << "Dequeuing the costly way..." << endl;

 for (int trials = 1; trials <= numTrials; trials++){

    Queue DequeueCostlyQueue; // Create an empty queue
    
    for (int i = 0; i < queueSize; i++){
        
        int value = 1 + rand() % maxValue;
        
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        DequeueCostlyQueue.enqueueCheaper(value);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::micro> enqueueTime_micro = t2 - t1;
        totalEnqueuingTime += enqueueTime_micro.count();
    
    }

    while (!DequeueCostlyQueue.isEmpty()){
        
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        DequeueCostlyQueue.dequeueCostly();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::micro> dequeueTime_micro = t2 - t1;
        totalDequeuingTime += dequeueTime_micro.count();
        
    }
  }// trials loop
  
  
  cout << "Average Enqueuing Time (micro seconds) " << (totalEnqueuingTime)/(numTrials*queueSize) << endl;
  cout << "Average Dequeuing Time (micro seconds) " << (totalDequeuingTime)/(numTrials*queueSize) << endl;
  



  
  system("pause");

  
return 0;
}
