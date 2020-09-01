#include <iostream>
#include <stdlib.h> //srand, rand
#include <time.h>//clock_t, clock, CLOCKS_PER_SEC
using namespace std;

// implementing a doubly linked list-based queue


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

class Queue{

    private:
        Node* headPtr;
        Node* tailPtr;

    
    public:
        Queue(){
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
        
        
        void enqueue(int data){
            
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

        
        int dequeue(){
            
            Node* firstNodePtr = headPtr->getNextNodePtr();
            Node* nextNodePtr = 0;
            
            int poppedData = -100000; //empty queue
            
            if (firstNodePtr != 0){
                nextNodePtr = firstNodePtr->getNextNodePtr();
                poppedData = firstNodePtr->getData();
            }
            else
                return poppedData;
            
            if (nextNodePtr != 0){
                nextNodePtr->setPrevNodePtr(0);
                headPtr->setNextNodePtr(nextNodePtr);
            }
            else{
                headPtr->setNextNodePtr(0);
                tailPtr->setPrevNodePtr(0);
            }

            return poppedData;
            
        }
        
        
        int peek(){
            
            Node* firstNodePtr = headPtr->getNextNodePtr();
            
            if (firstNodePtr != 0)
                return firstNodePtr->getData();
            else
                return -100000; //empty queue
                
        }
    

        
};



int getQueueLength(Queue queue){
            
    int length = 0;
    
    Node* headPtr = queue.getHeadPtr();
    Node* currentNodePtr = headPtr->getNextNodePtr();
    
    while (currentNodePtr != 0){
        length++;
        currentNodePtr = currentNodePtr->getNextNodePtr();
    }
    
    return length;
            
}



void Print(Queue queue){
    
    int queueLength = getQueueLength(queue);
    
    for (int index = 0; index < queueLength; index++){
        int dataDequeued = queue.dequeue();
        cout << dataDequeued << " ";
        queue.enqueue(dataDequeued);
    }
    
    cout << endl;
    
}


void QueueInsertAtIndex(Queue queue, int insertIndex, int insertData){
    int size = getQueueLength(queue), counter = 0;

    if(insertIndex > size && insertIndex < 0) return;

    while(counter < size) {

        int top = queue.dequeue();

        if(counter == insertIndex)
            queue.enqueue(insertData);

        queue.enqueue(top);
        counter++;
    }

}

int QueueDeleteAtIndex(Queue queue, int deleteIndex){
     // Implement your code here
    int size = getQueueLength(queue), counter = 0;
    int deletedData = 0;
    
    if(deleteIndex > size) return -100000;
    
    while(counter < size) {
        int top = queue.dequeue();
 
        if(deleteIndex != counter)
            queue.enqueue(top);
        else
            deletedData = top;
        
        counter++;
    }
    
    return deletedData;
}











int main(){

    Queue queue;

    int queueSize;
    
    cout << "Enter the number of elements you want to enqueue: ";
    cin >> queueSize;
    
    srand(time(NULL));
    
    int maxValue;
    
    cout << "Enter the maximum value for an element: ";
    cin >> maxValue;

    cout << "Elements enqueued: ";
    for (int i = 0; i < queueSize; i++){
        
        int value = rand() % maxValue;
        queue.enqueue(value);
        cout << value << " ";
    }
    
    cout << endl;
    
    
    cout << "Queue before the insertion " << endl;
    Print(queue);
    
    int insertData;
    cout << "Enter the data to insert: ";
    cin >> insertData;
    
    int insertIndex;
    cout << "Enter the index to insert: ";
    cin >> insertIndex;
    
    QueueInsertAtIndex(queue, insertIndex, insertData);
    
    cout << "Queue after the insertion " << endl;
    Print(queue);

    
    int deleteIndex;
    cout << "Enter the index to delete: ";
    cin >> deleteIndex;
    
    QueueDeleteAtIndex(queue, deleteIndex);
    
    cout << "Queue after the deletion " << endl;
    Print(queue);


    
    system("pause");
    
return 0;
}

